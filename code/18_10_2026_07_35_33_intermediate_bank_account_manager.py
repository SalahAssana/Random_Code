# Bank Account Manager
class BankAccount:
    def __init__(self):
        self.accounts = {}

    def create_account(self, account_number):
        if account_number not in self.accounts:
            self.accounts[account_number] = {"balance": 0}
            print(f"Account {account_number} created.")
        else:
            print("Account already exists.")

    def deposit(self, account_number, amount):
        if account_number in self.accounts:
            self.accounts[account_number]["balance"] += amount
            print(f"Deposited ${amount} into account {account_number}.")
        else:
            print("Account does not exist.")

    def withdraw(self, account_number, amount):
        if account_number in self.accounts:
            if self.accounts[account_number]["balance"] >= amount:
                self.accounts[account_number]["balance"] -= amount
                print(f"Withdrew ${amount} from account {account_number}.")
            else:
                print("Insufficient funds.")
        else:
            print("Account does not exist.")

    def check_balance(self, account_number):
        if account_number in self.accounts:
            print(f"Balance of account {account_number}: ${self.accounts[account_number]['balance']}")
        else:
            print("Account does not exist.")

    def display_accounts(self):
        for account_number, details in self.accounts.items():
            print(f"Account {account_number} - Balance: ${details['balance']}")

def main():
    bank = BankAccount()

    while True:
        print("\nBank Account Manager")
        print("1. Create an account")
        print("2. Deposit funds")
        print("3. Withdraw funds")
        print("4. Check balance")
        print("5. Display all accounts")
        print("6. Quit")

        choice = input("Choose an option: ")

        if choice == "1":
            account_number = input("Enter a unique account number: ")
            bank.create_account(account_number)
        elif choice == "2":
            account_number = input("Enter the account number to deposit into: ")
            amount = float(input("Enter the amount to deposit: "))
            bank.deposit(account_number, amount)
        elif choice == "3":
            account_number = input("Enter the account number to withdraw from: ")
            amount = float(input("Enter the amount to withdraw: "))
            bank.withdraw(account_number, amount)
        elif choice == "4":
            account_number = input("Enter the account number to check balance for: ")
            bank.check_balance(account_number)
        elif choice == "5":
            bank.display_accounts()
        elif choice == "6":
            print("Goodbye!")
            break
        else:
            print("Invalid option. Please try again.")

if __name__ == '__main__':
    main()