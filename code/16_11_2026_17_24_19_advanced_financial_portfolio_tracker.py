# Financial Portfolio Tracker

import datetime as dt
from collections import defaultdict

class Transaction:
    def __init__(self, date: dt.datetime, asset: str, quantity: int, price: float):
        self.date = date
        self.asset = asset
        self.quantity = quantity
        self.price = price

class PortfolioTracker:
    def __init__(self):
        self.assets = defaultdict(dict)
        self.transactions = []

    def add_transaction(self, transaction: Transaction):
        self.transactions.append(transaction)
        if transaction.asset not in self.assets:
            self.assets[transaction.asset] = {}
        self.assets[transaction.asset][transaction.date] = (transaction.quantity, transaction.price)

    def get_portfolio_value(self, date: dt.datetime) -> float:
        total_value = 0
        for asset, transactions in self.assets.items():
            for t_date, (quantity, price) in transactions.items():
                if t_date <= date:
                    total_value += quantity * price
        return total_value

    def get_asset_values(self, date: dt.datetime) -> dict:
        assets = {}
        for asset, transactions in self.assets.items():
            total_quantity = 0
            total_value = 0
            for t_date, (quantity, price) in transactions.items():
                if t_date <= date:
                    total_quantity += quantity
                    total_value += quantity * price
            assets[asset] = {'value': total_value, 'quantity': total_quantity}
        return assets

def main():
    tracker = PortfolioTracker()

    # Synthetic data for demonstration purposes
    tracker.add_transaction(Transaction(dt.datetime(2022, 1, 1), 'AAPL', 100, 150.0))
    tracker.add_transaction(Transaction(dt.datetime(2022, 1, 15), 'AAPL', -50, 155.0))
    tracker.add_transaction(Transaction(dt.datetime(2022, 2, 1), 'GOOG', 200, 2500.0))
    tracker.add_transaction(Transaction(dt.datetime(2022, 2, 28), 'GOOG', -100, 2700.0))

    print("Portfolio value on 2022-02-28:", tracker.get_portfolio_value(dt.datetime(2022, 2, 28)))
    assets = tracker.get_asset_values(dt.datetime(2022, 2, 28))
    for asset, values in assets.items():
        print(f"{asset}: value={values['value']:.2f}, quantity={values['quantity']}")

if __name__ == '__main__':
    main()