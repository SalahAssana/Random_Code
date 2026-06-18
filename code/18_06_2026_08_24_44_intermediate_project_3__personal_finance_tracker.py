# Project 3: Personal Finance Tracker
import matplotlib.pyplot as plt
from datetime import date

class Expense:
    def __init__(self, amount, category):
        self.amount = float(amount)
        self.category = category

class Income:
    def __init__(self, amount, source):
        self.amount = float(amount)
        self.source = source

class Budget:
    def __init__(self, category, limit):
        self.category = category
        self.limit = float(limit)

class Tracker:
    def __init__(self):
        self.expenses = []
        self.incomes = []
        self.budgets = []

    def add_expense(self, expense):
        self.expenses.append(expense)

    def add_income(self, income):
        self.incomes.append(income)

    def add_budget(self, budget):
        self.budgets.append(budget)

    def calculate_balance(self):
        total_income = sum(income.amount for income in self.incomes)
        total_expense = sum(expense.amount for expense in self.expenses)
        return total_income - total_expense

    def visualize_budgets(self):
        categories = [budget.category for budget in self.budgets]
        limits = [budget.limit for budget in self.budgets]
        plt.bar(categories, limits)
        plt.xlabel('Category')
        plt.ylabel('Limit')
        plt.title('Budget Limits')
        plt.show()

    def visualize_expenses(self):
        categories = [expense.category for expense in self.expenses]
        amounts = [expense.amount for expense in self.expenses]
        plt.bar(categories, amounts)
        plt.xlabel('Category')
        plt.ylabel('Amount')
        plt.title('Expenses')
        plt.show()

def main():
    tracker = Tracker()

    today = date.today()
    income1 = Income(500.0, 'Salary')
    income2 = Income(200.0, 'Interest')
    expense1 = Expense(100.0, 'Rent')
    expense2 = Expense(50.0, 'Groceries')

    tracker.add_income(income1)
    tracker.add_income(income2)
    tracker.add_expense(expense1)
    tracker.add_expense(expense2)

    budget_rent = Budget('Rent', 800.0)
    budget_groceries = Budget('Groceries', 100.0)
    tracker.add_budget(budget_rent)
    tracker.add_budget(budget_groceries)

    print(f'Balance: ${tracker.calculate_balance():.2f}')
    tracker.visualize_budgets()
    tracker.visualize_expenses()

if __name__ == '__main__':
    main()