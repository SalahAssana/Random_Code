#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class Transaction:
    def __init__(self, date, description, amount):
        self.date = date
        self.description = description
        self.amount = amount

class Category:
    def __init__(self, name):
        self.name = name
        self.balance = 0.0

class FinanceManager:
    def __init__(self):
        self.transactions = []
        self.categories = {}

    def add_transaction(self, transaction):
        self.transactions.append(transaction)
        for category in self.categories.values():
            if transaction.description.startswith(category.name + " - "):
                category.balance += transaction.amount
                break

    def get_balance(self, category_name):
        return self.categories.get(category_name).balance

    def print_transactions(self):
        for t in sorted(self.transactions, key=lambda x: x.date):
            print(f"{t.date}: {t.description} - {t.amount:.2f}")

def main():
    finance_manager = FinanceManager()

    # Synthetic data
    transactions = [
        Transaction("2020-01-01", "Rent - January 2020", -1500.00),
        Transaction("2020-01-02", "Groceries - January 2020", -100.00),
        Transaction("2020-02-15", "Salary - February 2020", 4000.00),
        Transaction("2020-03-01", "Rent - March 2020", -1500.00),
    ]

    categories = ["Rent", "Groceries", "Salary"]

    for t in transactions:
        finance_manager.add_transaction(t)

    for category in categories:
        print(f"{category}: {finance_manager.get_balance(category):.2f}")

    finance_manager.print_transactions()

if __name__ == '__main__':
    main()