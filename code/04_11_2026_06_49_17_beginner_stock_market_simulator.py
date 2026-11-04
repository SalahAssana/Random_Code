import random
import statistics

# Define constants for stock market simulation
STOCK_PRICE_MIN = 10.0
STOCK_PRICE_MAX = 100.0
TRADING_DAYS = 30

if __name__ == '__main__':
    # Initialize a list to store daily stock prices
    stock_prices = []

    # Simulate random stock price data over the trading days
    for day in range(TRADING_DAYS):
        stock_price = random.uniform(STOCK_PRICE_MIN, STOCK_PRICE_MAX)
        stock_prices.append(stock_price)

    # Calculate and display basic statistics about the simulated stock market trends
    mean_stock_price = statistics.mean(stock_prices)
    median_stock_price = statistics.median(stock_prices)
    std_dev_stock_price = statistics.stdev(stock_prices)

    print("Simulated Stock Market Trends:")
    print(f"Mean: {mean_stock_price:.2f}")
    print(f"Median: {median_stock_price:.2f}")
    print(f"Standard Deviation: {std_dev_stock_price:.2f}")