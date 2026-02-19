import pandas as pd
import yfinance as yf
from datetime import datetime
import matplotlib.pyplot as plt

class Stock:
    def __init__(self, ticker):
        self.ticker = ticker
        self.data = yf.download(ticker, start='2020-01-01', end=datetime.today().strftime('%Y-%m-%d'))

    def get_returns(self):
        close_prices = self.data['Close'].values
        returns = []
        for i in range(1, len(close_prices)):
            return_ = (close_prices[i] - close_prices[i-1]) / close_prices[i-1]
            returns.append(return_)
        return returns

    def plot_returns(self):
        returns = self.get_returns()
        plt.plot(returns)
        plt.xlabel('Day')
        plt.ylabel('Return')
        plt.title(f'{self.ticker} Returns')
        plt.show()

class Portfolio:
    def __init__(self, stocks):
        self.stocks = stocks

    def get_portfolio_returns(self):
        returns = []
        for stock in self.stocks:
            returns.extend(stock.get_returns())
        return returns

    def plot_portfolio_returns(self):
        portfolio_returns = self.get_portfolio_returns()
        plt.plot(portfolio_returns)
        plt.xlabel('Day')
        plt.ylabel('Return')
        plt.title('Portfolio Returns')
        plt.show()

def main():
    stock1 = Stock('AAPL')
    stock2 = Stock('MSFT')
    portfolio = Portfolio([stock1, stock2])
    portfolio.plot_portfolio_returns()
    for stock in [stock1, stock2]:
        stock.plot_returns()

if __name__ == '__main__':
    main()