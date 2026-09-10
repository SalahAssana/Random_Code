# Bank Account Manager
import datetime

class BankAccount:
    def __init__(self, account_number, initial_balance=0):
        self.account_number = account_number
        self.balance = initial_balance
        self.transactions = []

    def deposit(self, amount):
        if amount > 0:
            self.balance += amount
            self.transactions.append({"type": "deposit", "amount": amount})
        else:
            print("Invalid deposit amount")

    def withdraw(self, amount):
        if 0 < amount <= self.balance:
            self.balance -= amount
            self.transactions.append({"type": "withdrawal", "amount": amount})
        elif amount > self.balance:
            print("Insufficient funds")
        else:
            print("Invalid withdrawal amount")

    def get_balance(self):
        return self.balance

    def get_transactions(self):
        return self.transactions


class BankAccountManager:
    def __init__(self):
        self.accounts = {}

    def create_account(self, account_number, initial_balance=0):
        if account_number not in self.accounts:
            self.accounts[account_number] = BankAccount(account_number, initial_balance)
            print(f"Account {account_number} created with an initial balance of ${initial_balance}")
        else:
            print("Account already exists")

    def deposit(self, account_number, amount):
        if account_number in self.accounts:
            self.accounts[account_number].deposit(amount)
        else:
            print("Account does not exist")

    def withdraw(self, account_number, amount):
        if account_number in self.accounts:
            self.accounts[account_number].withdraw(amount)
        else:
            print("Account does not exist")

    def get_balance(self, account_number):
        if account_number in self.accounts:
            return self.accounts[account_number].get_balance()
        else:
            print("Account does not exist")
            return None

    def get_transactions(self, account_number):
        if account_number in self.accounts:
            return self.accounts[account_number].get_transactions()
        else:
            print("Account does not exist")
            return None


# Main program
if __name__ == '__main__':
    manager = BankAccountManager()

    # Create accounts
    manager.create_account("1234567890", 10000)
    manager.create_account("9876543210", 5000)

    # Perform transactions
    manager.deposit("1234567890", 2000)
    manager.withdraw("1234567890", 1500)
    manager.deposit("9876543210", 3000)
    manager.withdraw("9876543210", 2500)

    # Get account balances and transactions
    balance1 = manager.get_balance("1234567890")
    print(f"Account 1234567890 balance: ${balance1}")
    transactions1 = manager.get_transactions("1234567890")
    for transaction in transactions1:
        if transaction["type"] == "deposit":
            print(f"Deposit of ${transaction['amount']} on {datetime.datetime.now()}")
        elif transaction["type"] == "withdrawal":
            print(f"Withdrawal of ${transaction['amount']} on {datetime.datetime.now()}")

    balance2 = manager.get_balance("9876543210")
    print(f"Account 9876543210 balance: ${balance2}")
    transactions2 = manager.get_transactions("9876543210")
    for transaction in transactions2:
        if transaction["type"] == "deposit":
            print(f"Deposit of ${transaction['amount']} on {datetime.datetime.now()}")
        elif transaction["type"] == "withdrawal":