import datetime as dt
from collections import defaultdict
from copy import deepcopy

class Transaction:
    def __init__(self, date: str, description: str, amount: float):
        self.date = dt.datetime.strptime(date, "%Y-%m-%d").date()
        self.description = description
        self.amount = float(amount)

class Category:
    def __init__(self, name: str):
        self.name = name
        self.balance = 0.0

    def add_transaction(self, transaction: Transaction) -> None:
        self.balance += transaction.amount

    def get_balance(self) -> float:
        return self.balance

class Budget:
    def __init__(self, categories: dict):
        self.categories = {k: Category(v) for k, v in categories.items()}

    def add_transaction(self, category: str, transaction: Transaction) -> None:
        if category not in self.categories:
            raise ValueError(f"Category '{category}' does not exist.")
        self.categories[category].add_transaction(transaction)

    def get_balance(self, category: str) -> float:
        return self.categories.get(category, Category("Unknown")).get_balance()

class PersonalFinanceTracker:
    def __init__(self):
        self.budget = Budget({"Food": 500.0, "Transportation": 200.0, "Entertainment": 100.0})
        self.transactions = []

    def add_transaction(self, transaction: Transaction) -> None:
        self.transactions.append(transaction)
        for category in ["Food", "Transportation", "Entertainment"]:
            if category in transaction.description:
                self.budget.add_transaction(category, transaction)

    def get_balance(self, category: str) -> float:
        return self.budget.get_balance(category)

def main():
    tracker = PersonalFinanceTracker()
    
    transactions = [
        Transaction("2022-01-01", "Food: Groceries $100.0", 100.0),
        Transaction("2022-01-15", "Transportation: Gas $50.0", 50.0),
        Transaction("2022-02-01", "Entertainment: Movie Night $20.0", 20.0),
        Transaction("2022-03-01", "Food: Dinner at Restaurant $30.0", 30.0)
    ]
    
    for transaction in transactions:
        tracker.add_transaction(transaction)
    
    print(f"Current balance for Food: {tracker.get_balance('Food')}")
    print(f"Current balance for Transportation: {tracker.get_balance('Transportation')}")
    print(f"Current balance for Entertainment: {tracker.get_balance('Entertainment')}")

if __name__ == '__main__':
    main()