import random
from collections import defaultdict
from abc import ABC, abstractmethod

class Stock:
    def __init__(self, ticker):
        self.ticker = ticker
        self.price_history = []

    def add_price(self, price):
        self.price_history.append(price)

    def get_average_price(self):
        return sum(self.price_history) / len(self.price_history)


class Portfolio(ABC):
    @abstractmethod
    def buy(self, stock: Stock, quantity):
        pass

    @abstractmethod
    def sell(self, stock: Stock, quantity):
        pass


class SimplePortfolio(Portfolio):
    def __init__(self):
        self.stocks = defaultdict(int)

    def buy(self, stock: Stock, quantity):
        if not isinstance(stock, Stock):
            raise TypeError("Invalid stock type")
        if quantity < 1:
            raise ValueError("Quantity must be at least 1")
        self.stocks[stock.ticker] += quantity

    def sell(self, stock: Stock, quantity):
        if not isinstance(stock, Stock):
            raise TypeError("Invalid stock type")
        if quantity < 1:
            raise ValueError("Quantity must be at least 1")
        if self.stocks[stock.ticker] - quantity < 0:
            raise ValueError(f"Not enough shares of {stock.ticker} to sell")
        self.stocks[stock.ticker] -= quantity


class MarketSimulator:
    def __init__(self):
        self.stocks = [Stock(f"STOCK_{i}") for i in range(10)]
        self.portfolio = SimplePortfolio()

    def simulate(self, days=30):
        for _ in range(days):
            for stock in self.stocks:
                price = random.uniform(0.1, 100)
                stock.add_price(price)
            print(f"Day {self.stocks[0].price_history.index(max(self.stocks[0].price_history)) + 1}:")
            for stock in self.stocks:
                print(f"{stock.ticker}: ${stock.get_average_price():.2f}")
            if input("Press Enter to continue, or 'q' to quit: ") == 'q':
                break
        self.print_portfolio()

    def print_portfolio(self):
        total_value = 0
        for stock, quantity in self.portfolio.stocks.items():
            value = quantity * self.stocks[stock].get_average_price()
            print(f"{self.stocks[stock].ticker}: {quantity} shares @ ${self.stocks[stock].get_average_price():.2f} = ${value:.2f}")
            total_value += value
        print(f"Total portfolio value: ${total_value:.2f}")


if __name__ == '__main__':
    simulator = MarketSimulator()
    simulator.simulate()