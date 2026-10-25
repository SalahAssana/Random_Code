import random
from collections import defaultdict
from datetime import datetime

class Stock:
    def __init__(self, symbol, initial_price):
        self.symbol = symbol
        self.price = initial_price
        self.history = [(datetime.now(), initial_price)]

    def update_price(self, new_price):
        self.price = new_price
        self.history.append((datetime.now(), new_price))

class Portfolio:
    def __init__(self):
        self.stocks = {}
        self.cash = 10000.0

    def buy_stock(self, stock: Stock, quantity):
        if stock.symbol not in self.stocks:
            self.stocks[stock.symbol] = {'quantity': 0, 'value': 0}
        total_cost = quantity * stock.price
        if self.cash >= total_cost:
            self.cash -= total_cost
            self.stocks[stock.symbol]['quantity'] += quantity
            self.stocks[stock.symbol]['value'] += total_cost
        else:
            print("Insufficient cash")

    def sell_stock(self, stock: Stock, quantity):
        if stock.symbol in self.stocks and self.stocks[stock.symbol]['quantity'] >= quantity:
            total_revenue = quantity * stock.price
            self.cash += total_revenue
            self.stocks[stock.symbol]['quantity'] -= quantity
            self.stocks[stock.symbol]['value'] -= total_revenue
        else:
            print("Insufficient stock")

    def get_portfolio_value(self):
        return sum([self.stocks[symbol]['value'] for symbol in self.stocks])

class StockMarketSimulator:
    def __init__(self):
        self.portfolio = Portfolio()
        self.stocks = defaultdict(Stock)

    def run_simulation(self, days=30):
        stock_symbols = ['AAPL', 'GOOG', 'MSFT']
        initial_prices = [random.uniform(50.0, 150.0) for _ in range(len(stock_symbols))]
        for symbol, price in zip(stock_symbols, initial_prices):
            self.stocks[symbol] = Stock(symbol, price)
        for day in range(days):
            for stock_symbol, stock_price in self.stocks.items():
                change = random.uniform(-5.0, 5.0)
                new_price = stock_price.price * (1 + change/100)
                self.stocks[stock_symbol].update_price(new_price)
            print(f"Day {day+1}:")
            for symbol in stock_symbols:
                print(f"{symbol}: {self.stocks[symbol].price:.2f}")
            print(f"Portfolio value: {self.portfolio.get_portfolio_value():.2f}")
            self.portfolio.buy_or_sell()
        print("Simulation complete")

    def buy_or_sell(self):
        user_input = input("Buy or sell? (b/s) ")
        if user_input.lower() == 'b':
            stock_symbol = input("Enter stock symbol: ")
            quantity = float(input("Enter quantity: "))
            self.portfolio.buy_stock(self.stocks[stock_symbol], quantity)
        elif user_input.lower() == 's':
            stock_symbol = input("Enter stock symbol: ")
            quantity = float(input("Enter quantity: "))
            self.portfolio.sell_stock(self.stocks[stock_symbol], quantity)

if __name__ == '__main__':
    simulator = StockMarketSimulator()
    simulator.run_simulation()