-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Looks at the crime reports for information gathering
SELECT id, street, description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28


-- Look at the bakery_security_logs for information gathering
SELECT license_plate, hour, minute, activity FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour <= 10;

-- Group all the same license_plate in bakery_security_logs
SELECT license_plate, hour, minute, activity
FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour <= 10
ORDER BY license_plate ASC, hour ASC, minute ASC;

-- Gather more information with the interviews
SELECT name, day, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

-- Gather info about the ATM database
SELECT day, account_number, atm_location, transaction_type
FROM ATM_transactions
WHERE atm_location = "Leggett Street"
    AND transaction_type = "withdraw"
    AND year = 2021 AND month = 7 AND day = 28;

-- Gather info about the booked flight at 7/29/2021
SELECT  id, origin_airport_id, destination_airport_id
        , day, hour
FROM Flights
WHERE year = 2021 AND month = 7 AND day = 29
ORDER BY hour ASC;


-- Gather info about the call duration within less than a minute
SELECT id, year, day, duration
FROM Phone_calls
WHERE   month = 7 AND day = 28
        AND duration <= 60
ORDER BY id ASC;


-- Gather info about bank accounts, airports and people
SELECT * FROM Bank_accounts;
SELECT * FROM airports;
SELECT * FROM passengers;
SELECT * FROM people;


-- Combine Data of Bank_accounts and ATM Transaction
SELECT day, ATM_transactions.account_number, atm_location, transaction_type, creation_year, person_id
FROM ATM_transactions
JOIN Bank_accounts
    ON ATM_transactions.account_number = Bank_accounts.account_number
WHERE atm_location = "Leggett Street"
    AND transaction_type = "withdraw"
    AND year = 2021 AND month = 7 AND day = 28;


-- I use the Bank_accounts.person_id to trace the name of the people who made a withdraw at that day
SELECT person_id, name, license_plate, passport_number, phone_number
FROM ATM_transactions
JOIN Bank_accounts
    ON ATM_transactions.account_number = Bank_accounts.account_number
JOIN People
    ON People.id = Bank_accounts.person_id
WHERE atm_location = "Leggett Street"
    AND transaction_type = "withdraw"
    AND year = 2021 AND month = 7 AND day = 28;

-- Let's find out the info of Bruce
SELECT * FROM people WHERE name = "Bruce";

-- We find out if a suspected person is on the flight logs
SELECT DISTINCT flight_id, origin_airport_id, destination_airport_id
FROM Passengers
JOIN flights
    ON Passengers.flight_id = flights.id
WHERE flights.id IN
    (   SELECT flight_id
        FROM Passengers
        WHERE passport_number = 5773159633
    );


-- Let's see who the receiver of the call of Bruce was
SELECT * FROM phone_calls WHERE caller = "(367) 555-5533" AND day = 28;

-- Let's find out who receiver (375) 555-8161 number belongs to
SELECT * FROM people WHERE phone_number = "(375) 555-8161";