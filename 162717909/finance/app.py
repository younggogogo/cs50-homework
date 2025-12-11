import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

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
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("SYMBOL IS EMPTY", 400)
        if not shares:
            return apology("SHARES IS EMPTY", 400)
        information = lookup(symbol)

        if not information:
            return apology("INVALID SYMBOL", 400)
        try:
            shares=int(shares)
        except ValueError:
            return apology("INVALID SHARES",400)

        id = session["user_id"]
        rows = db.execute(
            "SELECT * FROM users where id=?",id
        )[0]

        cash=rows["cash"]


        current_price=information["price"]
        symbol=information["symbol"]

        money = current_price * shares
        if money > cash:
            return apology("Not enough money", 400)
        else:
            cash = cash - money
            db.execute(
                "UPDATE users SET cash=? WHERE id=?",cash,id
            )
            db.execute(
                "INSERT INTO history(userid,symbol,trade_price,trade_shares) VALUES(?,?,?,?)",
                id,symbol,current_price,shares
            )
            hold = db.execute(
                "SELECT * FROM user_holdings WHERE userid=? AND symbol =?",id,symbol
            )
            if hold:
                hold = hold[0]
                old_total=hold["total_shares"]
                old_price=hold["total_price"]
                new_total=old_total + shares
                new_price=old_price + money
                new_avg_price=new_price / new_total

                db.execute(
                    "UPDATE user_holdings SET total_shares=?,avg_price=?,total_price=? WHERE userid = ? AND symbol = ?"
                        ,new_total,new_avg_price,new_price,id,symbol
                )
            else:
                db.execute(
                    "INSERT INTO user_holdings(userid,symbol,total_shares,avg_price,total_price) VALUES(?,?,?,?,?) ",
                    id,symbol,shares,current_price,money
                )

            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
    if request.method =="POST":
        quote = request.form.get("quote")
        if not quote:
            return apology("SYMBOL IS EMPTY", 400)
        outcome = lookup(quote)
        if  not outcome:
            return apology("STMBOL IS INVALID", 400)
        else:
            outcome = "A Share of " + outcome["name"] + "(" + outcome["symbol"] +  ")" + " cost $" + str(outcome["price"])
            return render_template("quoted.html",outcome=outcome)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        username = request.form.get("username")
        if  not username:
            return apology("USER NAME IS EMPTY", 400)
        if not password:
            return apology("PASSWORD IS EMPTY", 400)
        if password != confirmation:
            return apology("PASSWORD DONT MATCH", 400)
        try:
            id = db.execute(
                "INSERT INTO users (username,hash)VALUES(?,?)",username,
                generate_password_hash(password)
            )
            session["user_id"]=id
            return redirect("/")
        except ValueError:
            return apology("THE USER IS EXISTENCE",400)

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
