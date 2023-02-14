import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

username = "asdasd"
symbol = "CYCLE"
hello = lookup(symbol)
share_quantity = db.execute("SELECT EXISTS(SELECT username FROM users WHERE username=?) AS Result", "gigaSec")

if hello == None:
    print("NoneNonenone")
else:
    print("Nothing happened")