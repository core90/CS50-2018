import os

from datetime import datetime
from cs50 import SQL, eprint
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    rows = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])

    """avg_price = db.execute("SELECT AVG(price) FROM portfolio WHERE user_id = :user_id GROUP BY stock ORDER BY buy_date asc", user_id=session["user_id"])
    eprint(avg_price)

    for line in avg_price:
        line["avgprice"] = usd(line)
    eprint(avgprice)"""

    # initalisize var to accumulate
    total_value = 0

    # iterate over database
    for lines in rows:
        symbol = str(lines["stock"])
        quote = lookup(symbol)
        lines["name"] = (quote['name'])
        lines["currentprice"] = usd(quote['price'])
        lines["price_buy"] = usd(lines['price'])
        lines["value_shares"] = usd(lines["shares"] * (quote["price"]))
        total_value += (lines['shares'] * quote['price'])

    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session['user_id'])

    # use usd function if needed
    quote_cash = usd(cash[0]['cash'])
    current_money = cash[0]['cash']
    summe = total_value + current_money
    finalsum = usd(summe)

    return render_template("index.html", rows=rows, quote_cash=quote_cash, finalsum=finalsum)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        stock = lookup(request.form.get("symbol"))

        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("enter stock symbol and number of shares", 400)

        elif not stock:
            return apology("stock does not exist", 400)

        while True:
            try:
                shares = int(request.form.get("shares"))
                break
            except ValueError:
                return apology("please provide positive number of shares", 400)

        if shares <= 0:
            return apology("please provide positive number of shares", 400)

        name = str(stock['name'])
        symbol = str(stock['symbol'])
        price = float(stock['price'])
        # eprint(symbol)
        credit = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session['user_id'])[0]["cash"]
        stock_cost = float(shares * price)

        # check if stock already exists in portfolio
        stock_db = db.execute("SELECT stock FROM portfolio WHERE stock = :stock AND user_id = :user_id",
                              stock=symbol, user_id=session['user_id'])

        # if stock not exists in portfolio, set var to none
        if stock_db == []:
            stock_exist = None
        else:
            stock_exist = stock_db[0]["stock"]

        # check if user has enough money
        if credit >= stock_cost:
            # if stock already exists, update; else insert new row
            if stock_exist == symbol:
                trans_update = db.execute("UPDATE portfolio SET shares = shares + :shares WHERE stock = :stock AND user_id = :user_id",
                                          shares=shares, stock=symbol, user_id=session['user_id'])

            else:
                transaction = db.execute("INSERT INTO portfolio(stock, stock_name, price, shares, buy_date, user_id) VALUES(:stock, :name, :price, :shares, :date, :user_id)",
                                         stock=symbol, name=name, price=price, shares=shares, date=datetime.now(), user_id=session["user_id"])

            # insert data for history table
            db.execute("INSERT INTO history(stock, stock_name, price, shares, user_id, status, time) VALUES(:stock, :name, :price, :shares, :user_id, :status, :time)",
                       stock=symbol, name=name, price=price, shares=shares, user_id=session["user_id"], status="BOUGHT", time=datetime.now().strftime("%Y-%m-%d %H:%M:%S"))

            # update users cash
            payment = db.execute("UPDATE users SET cash = cash - :stock_cost WHERE id = :user_id",
                                 stock_cost=stock_cost, user_id=session['user_id'])

            flash('Bought!')

            return redirect("/")

        else:
            return apology("not enough cash", 400)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute("SELECT * from history WHERE user_id = :user_id", user_id=session["user_id"])

    # initalisize var to accumulate
    total_value = 0

    # iterate over database
    for lines in rows:
        symbol = str(lines["stock"])
        quote = lookup(symbol)
        lines["name"] = (quote['name'])
        lines["currentprice"] = usd(quote['price'])
        lines["price"] = usd(lines['price'])
        if lines["shares"] > 0:
            lines["value_shares"] = usd(lines["shares"] * (quote["price"]))
        else:
            lines["value_shares"] = usd(lines["shares"] * (quote["price"] * -1))

    return render_template("history.html", rows=rows)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        flash("Login successful!")

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

        if not request.form.get("symbol"):
            return apology("must provide stock", 400)

        search = lookup(request.form.get("symbol"))

        if not search:
            return apology("stock not found", 400)

        else:
            return render_template("quoted.html", stock=search)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # ensure password was confirmed
        elif not request.form.get("confirmation"):
            return apology("confirm password", 400)

        # ensure password and confirm password do match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password does not match", 400)

        # ensure username is not already taken
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if len(rows) == 1:
            return apology("username already taken", 400)

        # insert user to database and log him into session
        session["user_id"] = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get
                                        ("username"), hash=generate_password_hash(request.form.get("password")))

        # return to homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        stock = lookup(request.form.get("symbol"))
        name = str(stock['name'])
        symbol = str(stock['symbol'])
        price = float(stock['price'])

        if not stock:
            return apology("must provide symbol", 402)

        elif not request.form.get("shares"):
            return apology("must provide number of shares", 403)

        while True:
            try:
                shares = int(request.form.get("shares"))
                break
            except ValueError:
                return apology("please provide positive number of shares", 401)

        if shares <= 0:
            return apology("please provide positive number of shares", 406)

        # qhery database for current cash balance
        cash = db.execute("SELECT cash From users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]

        # query database for the sum of shares of a stock
        shares_owned = db.execute("SELECT SUM(shares) FROM portfolio WHERE user_id = :user_id AND stock = :stock",
                                  user_id=session["user_id"], stock=stock["symbol"])
        shares_sum = shares_owned[0]["SUM(shares)"]

        # check if user have enough shares
        if shares_sum < shares:
            return apology("you have not enough shares", 400)

        else:
            # calculate current stock_price
            stock_cost = float(shares * price)

            # update cash balance
            cash_balance = db.execute("UPDATE users SET cash = cash + :stock_cost WHERE id = :user_id",
                                      stock_cost=stock_cost, user_id=session["user_id"])
            # convert shares to negative for history table
            shares_negative = shares * -1

            # insert data into history table
            db.execute("INSERT INTO history(stock, stock_name, price, shares, user_id, status, time) VALUES(:stock, :stock_name, :price, :shares, :user_id, :status, :time)",
                       stock=symbol, stock_name=name, price=price, shares=shares_negative, user_id=session["user_id"], status="SOLD", time=datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
            # update shares amount
            shares_update = db.execute("UPDATE portfolio SET shares = :shares_sum - :shares WHERE stock = :stock AND user_id = :user_id",
                                       shares=shares, shares_sum=shares_sum, stock=stock["symbol"], user_id=session["user_id"])

            # delete rows with shares = 0
            shares_empty = db.execute("DELETE FROM portfolio WHERE shares = 0 AND user_id = :user_id AND stock = :stock",
                                      user_id=session["user_id"], stock=stock["symbol"])

        flash("Sold!")
        return redirect("/")

    else:
        stocks_owned = db.execute("SELECT stock, shares FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])
        return render_template("sell.html", stocks_owned=stocks_owned)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
