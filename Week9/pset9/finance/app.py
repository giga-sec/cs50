import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    purchases = db.execute("SELECT * FROM purchase WHERE id=?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    total = 0
    for purchase in purchases:
        total += (purchase['share_price'] * purchase['share_quantity'])
    total += cash[0]['cash']
    return render_template("index.html", purchases=purchases, cash=cash[0]['cash'], total_price=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol == "":
            return apology("Blank Symbol")
        lookup_value = lookup(symbol)
        if lookup_value == None:
            return apology("Doesn't exist")

        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                return apology("No Negative Number")
            user_id = session["user_id"]
            user_cash = db.execute("SELECT cash FROM users WHERE id=?", user_id)
            total_price = lookup_value['price'] * shares
            if total_price >= user_cash[0]['cash']:
                return apology("User cannot afford the number of shares at the current price")

            exists = db.execute("SELECT EXISTS(SELECT symbol FROM purchase WHERE symbol=?) as exist", symbol)
            # Update History
            date = db.execute("SELECT CURRENT_TIMESTAMP")

            db.execute("INSERT INTO history (symbol, share_price, share_quantity, transacted_date) VALUES (?, ?, ?, ?)", \
                       symbol, lookup_value['price'], shares, date[0]['CURRENT_TIMESTAMP'])

            if exists[0]['exist'] == 0:
                db.execute("INSERT INTO purchase (id, symbol, company_name, share_price, share_quantity) VALUES (?, ?, ?, ?, ?)", \
                           user_id, symbol, lookup_value['name'], lookup_value['price'], shares)
            else:
                previous_share = db.execute("SELECT share_quantity FROM purchase WHERE symbol=?", symbol)
                shares += previous_share[0]['share_quantity']
                db.execute("UPDATE purchase SET share_quantity = ? WHERE id = ? AND symbol=?;", shares, user_id, symbol)
            db.execute("UPDATE users SET cash = ? WHERE id = ?;", user_cash[0]['cash'] - total_price, user_id)

            return redirect("/")
        except ValueError:
            return apology("Is decimal, don't", 400)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history")
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if request.form.get("symbol") == "":
            return apology("Empty Input")
        lookup_value = lookup(request.form.get("symbol"))
        if lookup_value == None:
            return apology("Doesn't exist")
        return render_template("quoted.html",  lookup_value=lookup_value)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        name = request.form.get("username")
        user_password = request.form.get("password")
        confirm_pass = request.form.get("confirmation")

        if (name == ""):
            return apology("Empty Username")
        exists = db.execute("SELECT EXISTS(SELECT username FROM users WHERE username=?) AS exist", name)
        if (exists[0]["exist"] >= 1):
            return apology("Username already exists")
        if (user_password == ""):
            return apology("Empty Password")

        if (confirm_pass != user_password):
            return apology("Password isn't the same")

        # Registered Successfully
        pass_hash = generate_password_hash(user_password, method='pbkdf2:sha256', salt_length=16)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", name, pass_hash)
        return render_template("login.html")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        exists = db.execute("SELECT EXISTS(SELECT symbol FROM purchase WHERE symbol=?) AS exist", symbol)
        if exists[0]["exist"] == 0:
            return apology("You don't have stocks.")
        if request.form.get("symbol") == "":
            return apology("Select a symbol")
        if request.form.get("shares") == "":
            return apology("Empty Share")

        share_quantity = db.execute("SELECT share_quantity FROM purchase WHERE symbol=?", symbol)
        n_shares = int(request.form.get("shares"))  # to sell
        if n_shares > share_quantity[0]['share_quantity']:
            return apology("Exceeding Share")

        user_id = session["user_id"]
        lookup_value = lookup(symbol)
        db.execute("UPDATE purchase SET share_quantity = ? WHERE id = ? AND symbol = ?", \
                   share_quantity[0]['share_quantity'] - n_shares, user_id, symbol)
        date = db.execute("SELECT CURRENT_TIMESTAMP")
        db.execute("INSERT INTO history (symbol, share_price, share_quantity, transacted_date) VALUES (?, ?, ?, ?)", \
                   symbol, lookup_value['price'], n_shares, date[0]['CURRENT_TIMESTAMP'])

        return redirect("/")
    else:
        symbols = db.execute("SELECT symbol FROM purchase")
        return render_template("sell.html", symbols=symbols)


app.jinja_env.globals.update(lookup=lookup)

