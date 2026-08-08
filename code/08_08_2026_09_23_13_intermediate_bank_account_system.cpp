#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Define a struct to represent a bank account
struct BankAccount {
    string accountNumber;
    string accountHolderName;
    double balance;
};

// Function to create a new bank account
BankAccount createNewBankAccount() {
    BankAccount newAccount;
    cout << "Enter the account number: ";
    cin >> newAccount.accountNumber;
    cout << "Enter the account holder's name: ";
    cin.ignore();
    getline(cin, newAccount.accountHolderName);
    newAccount.balance = 0.0;
    return newAccount;
}

// Function to deposit money into a bank account
void depositMoney(BankAccount& account) {
    double amount;
    cout << "Enter the amount to deposit: ";
    cin >> amount;
    if (amount > 0) {
        account.balance += amount;
        cout << "Deposit successful. New balance: $" << account.balance << endl;
    } else {
        cout << "Invalid deposit amount." << endl;
    }
}

// Function to withdraw money from a bank account
void withdrawMoney(BankAccount& account, double amount) {
    if (amount > 0 && account.balance >= amount) {
        account.balance -= amount;
        cout << "Withdrawal successful. New balance: $" << account.balance << endl;
    } else {
        cout << "Insufficient funds or invalid withdrawal amount." << endl;
    }
}

// Function to display bank account information
void displayBankAccountInfo(const BankAccount& account) {
    cout << "Account Number: " << account.accountNumber << endl;
    cout << "Account Holder's Name: " << account.accountHolderName << endl;
    cout << "Balance: $" << account.balance << endl;
}

// Function to handle user input and perform actions on the bank account
void bankAccountMenu(BankAccount& account) {
    int choice;
    while (true) {
        cout << "1. Deposit money" << endl;
        cout << "2. Withdraw money" << endl;
        cout << "3. Check balance" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                depositMoney(account);
                break;
            case 2:
                double withdrawalAmount;
                cout << "Enter the amount to withdraw: ";
                cin >> withdrawalAmount;
                withdrawMoney(account, withdrawalAmount);
                break;
            case 3:
                displayBankAccountInfo(account);
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    BankAccount account = createNewBankAccount();
    bankAccountMenu(account);
    return 0;
}