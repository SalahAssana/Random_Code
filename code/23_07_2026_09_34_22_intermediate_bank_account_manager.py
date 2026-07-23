# Bank Account Manager

class BankAccount:
    def __init__(self, account_number, balance=0):
        self.account_number = account_number
        self.balance = balance

    def deposit(self, amount):
        if amount > 0:
            self.balance += amount
            return f"Deposited ${amount} into account {self.account_number}. New balance: ${self.balance}"
        else:
            return "Invalid deposit amount. Please enter a positive value."

    def withdraw(self, amount):
        if 0 < amount <= self.balance:
            self.balance -= amount
            return f"Withdrew ${amount} from account {self.account_number}. New balance: ${self.balance}"
        elif amount > self.balance:
            return "Insufficient funds. Please check your account balance."
        else:
            return "Invalid withdrawal amount. Please enter a positive value."

class BankAccountManager:
    def __init__(self):
        self.accounts = []

    def add_account(self, account_number, initial_balance=0):
        if not any(account.account_number == account_number for account in self.accounts):
            self.accounts.append(BankAccount(account_number, initial_balance))
            return f"Added account {account_number} with initial balance ${initial_balance}."
        else:
            return "Account already exists. Please enter a unique account number."

    def get_account(self, account_number):
        for account in self.accounts:
            if account.account_number == account_number:
                return account
        return None

    def manage_accounts(self):
        while True:
            print("\n1. Add Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. Exit")
            choice = input("Choose an option: ")
            if choice == '1':
                account_number = input("Enter account number: ")
                initial_balance = float(input("Enter initial balance (default=0): ") or 0)
                print(self.add_account(account_number, initial_balance))
            elif choice == '2':
                account_number = input("Enter account number: ")
                amount = float(input("Enter deposit amount: "))
                account = self.get_account(account_number)
                if account:
                    print(account.deposit(amount))
                else:
                    print("Account not found.")
            elif choice == '3':
                account_number = input("Enter account number: ")
                amount = float(input("Enter withdrawal amount: "))
                account = self.get_account(account_number)
                if account:
                    print(account.withdraw(amount))
                else:
                    print("Account not found.")
            elif choice == '4':
                account_number = input("Enter account number: ")
                account = self.get_account(account_number)
                if account:
                    print(f"Account {account_number} balance: ${account.balance}")
                else:
                    print("Account not found.")
            elif choice == '5':
                print("Exiting...")
                break
            else:
                print("Invalid option. Please choose a valid option.")

if __name__ == '__main__':
    manager = BankAccountManager()
    manager.manage_accounts()