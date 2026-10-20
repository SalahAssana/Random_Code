from abc import ABC, abstractmethod
import random
import matplotlib.pyplot as plt

class Stock(ABC):
    @abstractmethod
    def get_price(self) -> float:
        pass

class RealStock(Stock):
    def __init__(self, symbol: str, price: float):
        self.symbol = symbol
        self.price = price

    def get_price(self) -> float:
        return self.price

class FakeStock(Stock):
    def __init__(self, symbol: str):
        self.symbol = symbol
        self.price_history = []

    def add_price_data(self, date: str, price: float):
        self.price_history.append((date, price))

    def get_price(self) -> float:
        return random.choice([p[1] for p in self.price_history])

class Portfolio:
    def __init__(self):
        self.stocks = {}

    def add_stock(self, stock: Stock, quantity: int):
        if isinstance(stock, FakeStock):
            for date, price in stock.price_history:
                print(f"Added {date} price data to {stock.symbol}")
        self.stocks[stock.symbol] = quantity

    def get_portfolio_value(self) -> float:
        value = 0
        for symbol, quantity in self.stocks.items():
            if isinstance(stock := self.stocks[symbol], FakeStock):
                value += stock.get_price() * quantity
            else:
                value += (stock.get_price() or 0) * quantity
        return value

class Trader:
    def __init__(self):
        self.portfolio = Portfolio()

    def buy(self, stock: Stock, quantity: int):
        if isinstance(stock, FakeStock):
            print(f"Buying {quantity} shares of {stock.symbol}")
        self.portfolio.add_stock(stock, quantity)

    def sell(self, stock: Stock, quantity: int):
        if isinstance(stock, FakeStock):
            print(f"Selling {quantity} shares of {stock.symbol}")
        if quantity > 0 and self.portfolio.stocks.get(stock.symbol) >= quantity:
            self.portfolio.stocks[stock.symbol] -= quantity
        else:
            print("Not enough shares to sell")

    def get_portfolio_value(self) -> float:
        return self.portfolio.get_portfolio_value()

def simulate_market( trader: Trader, stock_data: dict, days: int):
    for _ in range(days):
        for symbol, data in stock_data.items():
            if isinstance(stock := RealStock(symbol, data), FakeStock):
                continue
            for i in range(len(data) - 1):
                stock.add_price_data(f"Day {i+1}", data[i])
        trader.buy(RealStock("AAPL", random.choice([p[1] for p in [(date, price) for date, price in RealStock("AAPL", data).price_history]])), 100)
        trader.sell(RealStock("GOOG", random.choice([p[1] for p in [(date, price) for date, price in RealStock("GOOG", data).price_history]])), 50)
    return trader.get_portfolio_value()

def main():
    if __name__ == '__main__':
        stock_data = {"AAPL": [100, 105, 110], "GOOG": [500, 520, 550]}
        trader = Trader()
        portfolio_value = simulate_market(trader, stock_data, 3)
        print(f"Final Portfolio Value: {portfolio_value}")
        plt.plot([100, 105, 110])
        plt.show()

if __name__ == '__main__':
    main()