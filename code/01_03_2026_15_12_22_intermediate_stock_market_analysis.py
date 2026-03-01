# Stock Market Analysis
import matplotlib.pyplot as plt
from datetime import datetime

class Stock:
    def __init__(self, symbol, dates, prices):
        self.symbol = symbol
        self.dates = [datetime.strptime(date, "%Y-%m-%d") for date in dates]
        self.prices = prices

def calculate_daily_returns(stock):
    returns = []
    for i in range(1, len(stock.prices)):
        return_ = (stock.prices[i] - stock.prices[i-1]) / stock.prices[i-1]
        returns.append(return_)
    return returns

def plot_stock_price(stock):
    plt.plot([date.strftime("%Y-%m-%d") for date in stock.dates], stock.prices)
    plt.xlabel('Date')
    plt.ylabel('Price')
    plt.title(f'{stock.symbol} Stock Price')
    plt.show()

def plot_daily_returns(returns):
    plt.plot(range(len(returns)), returns)
    plt.xlabel('Day')
    plt.ylabel('Return')
    plt.title('Daily Returns')
    plt.show()

def main():
    stock = Stock("AAPL", ["2020-01-01", "2020-01-02", "2020-01-03"], [100, 105, 110])
    returns = calculate_daily_returns(stock)
    plot_stock_price(stock)
    plot_daily_returns(returns)

if __name__ == '__main__':
    main()