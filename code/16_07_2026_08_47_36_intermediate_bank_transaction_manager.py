# Bank Transaction Manager
class Transaction:
    def __init__(self, id, amount, type):
        self.id = id
        self.amount = float(amount)
        self.type = type

class Account:
    def __init__(self, account_number, balance=0.0):
        self.account_number = account_number
        self.balance = balance
        self.transactions = []

    def deposit(self, amount):
        self.balance += float(amount)
        self.transactions.append(Transaction(len(self.transactions), amount, "deposit"))

    def withdraw(self, amount):
        if self.balance >= float(amount):
            self.balance -= float(amount)
            self.transactions.append(Transaction(len(self.transactions), -amount, "withdrawal"))
        else:
            raise ValueError("Insufficient funds")

    def transfer(self, to_account, amount):
        if self.balance >= float(amount):
            self.balance -= float(amount)
            to_account.deposit(amount)
            self.transactions.append(Transaction(len(self.transactions), -amount, "transfer"))
            to_account.transactions.append(Transaction(len(to_account.transactions), amount, "deposit"))
        else:
            raise ValueError("Insufficient funds")

def print_transactions(account):
    if account.transactions:
        print(f"Account {account.account_number} transactions:")
        for transaction in account.transactions:
            print(f"{transaction.id}: {transaction.type} - ${transaction.amount:.2f}")
    else:
        print(f"No transactions found for Account {account.account_number}")

if __name__ == '__main__':
    account1 = Account("12345")
    account2 = Account("67890")

    try:
        account1.deposit(100.0)
        account1.withdraw(50.0)
        account1.transfer(account2, 20.0)

        print_transactions(account1)
        print_transactions(account2)
    except ValueError as e:
        print(f"Error: {e}")