#!/usr/bin/env python3
import os
import pandas as pd
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

class Transaction:
    def __init__(self, date, description, amount):
        self.date = date
        self.description = description
        self.amount = float(amount)

class Budget:
    def __init__(self, name):
        self.name = name
        self.income = 0.0
        self.expenses = []

    def add_expense(self, expense):
        self.expenses.append(expense)

    def calculate_balance(self):
        return sum([e.amount for e in self.expenses]) - self.income

class FinancialAdvisor:
    def __init__(self):
        self.budgets = []

    def add_budget(self, budget):
        self.budgets.append(budget)

    def plot_budgets(self):
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        for budget in self.budgets:
            ax.scatter([budget.calculate_balance()], [0], [1])
        ax.set_xlabel('Balance')
        ax.set_ylabel('Category')
        ax.set_zlabel('Budget')
        plt.show()

    def analyze_transactions(self):
        transactions = []
        for budget in self.budgets:
            for expense in budget.expenses:
                transactions.append(Transaction(expense.date, expense.description, -expense.amount))
            if budget.income > 0.0:
                transactions.append(Transaction(budget.name + ' Income', 'Income', budget.income))
        df = pd.DataFrame(transactions)
        plt.figure(figsize=(10,6))
        ax = df.plot.bar(x='date', y='amount')
        ax.set_title('Financial Transactions')
        ax.set_xlabel('Date')
        ax.set_ylabel('Amount')
        plt.show()

def main():
    advisor = FinancialAdvisor()
    advisor.add_budget(Budget('Living Expenses'))
    advisor.add_budget(Budget('Savings'))
    advisor.add_budget(Budget('Debt Repayment'))

    living_expenses = Budget('Living Expenses')
    living_expenses.add_expense(Transaction('2022-01-01', 'Rent', 1500.0))
    living_expenses.add_expense(Transaction('2022-02-15', 'Groceries', 500.0))

    savings = Budget('Savings')
    savings.add_expense(Transaction('2022-03-01', 'Deposit', 1000.0))

    debt_repayment = Budget('Debt Repayment')
    debt_repayment.add_expense(Transaction('2022-02-01', 'Credit Card Payment', 500.0))
    debt_repayment.add_expense(Transaction('2022-04-15', 'Student Loan Payment', 200.0))

    advisor.add_budget(living_expenses)
    advisor.add_budget(savings)
    advisor.add_budget(debt_repayment)

    advisor.plot_budgets()
    advisor.analyze_transactions()

if __name__ == '__main__':
    main()