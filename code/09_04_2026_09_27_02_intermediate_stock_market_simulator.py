def calculate_portfolio_value(portfolio, stock_prices):
    portfolio_value = 0
    for stock in portfolio:
        portfolio_value += stock['shares'] * stock_prices[stock['symbol']]
    return portfolio_value

def process_transaction(portfolio, transaction_type, symbol, shares):
    if transaction_type == 'buy':
        if symbol not in portfolio:
            portfolio[symbol] = {'shares': 0}
        portfolio[symbol]['shares'] += shares
    elif transaction_type == 'sell':
        if symbol not in portfolio or portfolio[symbol]['shares'] < shares:
            print("Insufficient shares to sell")
            return False
        portfolio[symbol]['shares'] -= shares
        if portfolio[symbol]['shares'] <= 0:
            del portfolio[symbol]
    return True

def main():
    # Synthetic data for stock prices and portfolio
    stock_prices = {'AAPL': 150.0, 'GOOG': 2000.0, 'MSFT': 250.0}
    portfolio = {'AAPL': {'shares': 100}, 'GOOG': {'shares': 50}}

    while True:
        transaction_type = input("Enter transaction type (buy/sell or q to quit): ")
        if transaction_type.lower() == 'q':
            break
        symbol = input("Enter stock symbol: ")
        shares = int(input("Enter number of shares: "))
        
        if not process_transaction(portfolio, transaction_type.lower(), symbol, shares):
            continue

    print(f"Final portfolio value: {calculate_portfolio_value(portfolio, stock_prices)}")

if __name__ == '__main__':
    main()