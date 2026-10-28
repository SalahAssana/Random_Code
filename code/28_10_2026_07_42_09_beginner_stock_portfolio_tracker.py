# Stock Portfolio Tracker
# A simple program to track and analyze a stock portfolio

class Stock:
    def __init__(self, symbol, quantity, price):
        self.symbol = symbol
        self.quantity = int(quantity)
        self.price = float(price)

    def calculate_value(self):
        return self.quantity * self.price

class Portfolio:
    def __init__(self):
        self.stocks = []

    def add_stock(self, stock):
        self.stocks.append(stock)

    def calculate_total_value(self):
        total_value = 0
        for stock in self.stocks:
            total_value += stock.calculate_value()
        return total_value

def main():
    # Create a portfolio
    portfolio = Portfolio()

    # Add some stocks to the portfolio
    apple_stock = Stock("AAPL", 100, 150.00)
    google_stock = Stock("GOOGL", 50, 2500.00)
    portfolio.add_stock(apple_stock)
    portfolio.add_stock(google_stock)

    # Calculate and print the total value of the portfolio
    total_value = portfolio.calculate_total_value()
    print(f"Total value of the portfolio: ${total_value:.2f}")

if __name__ == '__main__':
    main()