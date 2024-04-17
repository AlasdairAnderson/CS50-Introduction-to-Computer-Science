import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from decimal import *

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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
    # Get user's assests & currently owned stocks
    userAssets = db.execute("SELECT * FROM assets WHERE user_id = ?;", session["user_id"])

    # Get currently logged in user
    # User's current cash balance
    userInfo = db.execute("SELECT username, cash FROM users WHERE id =?;", session["user_id"])

    # Get current price of each owned stock
    stockInfo = []
    totalStocks = 0
    i = 0
    for stocks in userAssets:
        stockInfo = lookup(stocks["symbol"])
        # Total price of each stock held (shares * price)
        total = round(float(stockInfo["price"] * stocks["shares"]), 2)
        # See if i can add the total price strait into the stock info.
        stocks["price"] = stockInfo["price"]
        stocks["total"] = total
        totalStocks = round(totalStocks + total, 2)
        print(total, " ", totalStocks)
        i = i + 1

    # Users grand total (total value + cash)
    grandTotal = round(totalStocks + userInfo[0]["cash"], 2)

    return render_template("index.html", userInfo=userInfo, userAssets=userAssets, totalStocks=totalStocks, grandTotal=grandTotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Please enter a symbol", 400)
        stock = lookup(request.form.get("symbol"))
        if not request.form.get("shares"):
            return apology("Please enter the number of shares", 400)
        if not stock:
            return apology("Symbol does not exist", 400)

        shares = request.form.get("shares")
        if not shares.isdecimal():
            return apology("Please enter a whole number for shares", 400)
        if int(shares) < 1:
            return apology("Please a positive amount of shares", 400)

        totalprice = format(int(shares) * stock["price"], '.2f')
        usercash = db.execute("SELECT cash FROM users WHERE id IS ?", session["user_id"])
        userassets = db.execute("SELECT symbol FROM assets WHERE user_id = ? AND symbol = ?;", session["user_id"], stock["symbol"])
        timestamp = datetime.now()

        if (float(totalprice) > usercash[0]["cash"]):
            return apology("Not enough cash in account for purchase")

        updateCash = format(usercash[0]["cash"] - float(totalprice), '.2f')

        print(updateCash)

        db.execute("INSERT INTO purchases (user_id, ordertimestamp, symbol, price, shares, total, transation_type) VALUES (?, ?, ?, ?, ?, ?, ?);",
                   session["user_id"], timestamp, stock["symbol"], stock["price"], int(shares), totalprice, "purchase")
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updateCash, session["user_id"])

        # Add new stock to assets
        if not userassets:
            db.execute("INSERT INTO assets (user_id, symbol, shares) VALUES(?,?,?);", session["user_id"], stock["symbol"], shares)
        else:
            db.execute("UPDATE assets SET shares = shares + ? WHERE symbol = ? AND user_id = ?;",
                       shares, stock["symbol"], session["user_id"])

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM purchases WHERE user_id = ? UNION ALL SELECT * FROM sales WHERE user_id = ? ORDER BY ordertimestamp ;",
                         session["user_id"], session["user_id"])

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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
        symbolref = lookup(request.form.get("symbol"))
        if not symbolref:
            return apology("Invalid stock symbol")

        return render_template("quoted.html", symbolref=symbolref)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        existingUserName = db.execute("SELECT username FROM users WHERE username IS ?;", username)
        if not existingUserName:
            existingUserName = " "
        else:
            existingUserName = existingUserName[0]["username"]
        # Has user inputted user name
        if not request.form.get("username"):
            return apology("Please enter a username", 400)
        # Does username already exist
        if username == existingUserName:
            return apology("Username already taken", 400)
        # Has user inputted a password
        if not request.form.get("password"):
            return apology("Please enter a password", 400)
        # Does password and confirmation match?
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match", 400)
        # hash user's password
        passwordHash = generate_password_hash(password)

        # Upload user and password to db
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", username, passwordHash)
        return redirect("/")

    # User enter via GET
    else:
        return render_template("register.html")


@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():

    userCash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])

    if request.method == "POST" and request.form.get("password") or request.form.get("confirmPassword"):
        # Verify input
        if not request.form.get("password") or not request.form.get("confirmPassword"):
            return apology("Please enter a password and confirm it", 403)
        # Change Password

        newPassword = request.form.get("password")
        confirmPassword = request.form.get("confirmPassword")

        # Does password match
        if newPassword != confirmPassword:
            return apology("Password and confirm password is not the same", 403)

        passwordHash = generate_password_hash(newPassword)

        db.execute("UPDATE users SET hash = ? WHERE id = ?;", passwordHash, session["user_id"])

        return render_template("settings.html", userCash=userCash)

        # Add addtional cash to their account
    if request.method == "POST" and request.form.get("money"):
        # return apology("Please enter how much money you would like to add to your account", 403)
        if int(request.form.get("money")) < 1:
            return apology("Please enter an amount of money more than 1", 403)
        elif request.form.get("money"):
            cash = request.form.get("money")
            userCash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])

            cash = round(float(userCash[0]["cash"]) + float(cash), 2)

            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

    return render_template("settings.html", userCash=userCash)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # return failure statements
        if not request.form.get("symbol"):
            return apology("Please select a symbol")
        if not request.form.get("shares"):
            return apology("Please input a number of shares you would like to sell")

        stock = lookup(request.form.get("symbol"))
        print(stock)
        shares = int(request.form.get("shares"))
        print(shares)
        userassets = db.execute("SELECT * FROM assets WHERE symbol = ? AND user_id = ?", stock["symbol"], session["user_id"])

        print(userassets)
        # If unable to sell shares
        if shares < 1:
            return apology("Please input a posative number of shares you would like to sell")
        if shares > int(userassets[0]["shares"]):
            return apology("You do not have enough shares.")

        # If able to sell
        timestamp = datetime.now()
        usercash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        total = round(stock["price"] * shares, 2)

        # add transation to sales table
        db.execute("INSERT INTO sales (user_id, odertimestamp, symbol, price, shares, total, transation_type) VALUES(?,?,?,?,?,?,?);",
                   session["user_id"], timestamp, stock["symbol"], stock["price"], shares, total, "sale")
        # update assets to show that shares have been sold
        # If sold shares will take held stock to 0 delete asset
        if int(userassets[0]["shares"]) - shares == 0:
            db.execute("DELETE FROM assets WHERE symbol = ?;", stock["symbol"])
        else:
            remainingShares = int(userassets[0]["shares"]) - shares
            db.execute("UPDATE assets SET shares = ? WHERE symbol = ?;", remainingShares, stock["symbol"])
        # update cash in users
        updateCash = round(usercash[0]["cash"] + total, 2)
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", updateCash, session["user_id"])

        return redirect("/")

    # Get shares currently held by user
    usershares = db.execute("SELECT * FROM assets WHERE user_id = ?", session["user_id"])

    print(type(usershares), usershares)

    # Get current stock price
    for id in usershares:
        currentPrice = lookup(id["symbol"])
        id["price"] = currentPrice["price"]

    return render_template("sell.html", usershares=usershares)
