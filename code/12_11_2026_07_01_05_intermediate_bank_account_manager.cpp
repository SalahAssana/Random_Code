#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct BankAccount {
    string accountNumber;
    double balance;
};

void deposit(BankAccount& account, double amount) {
    account.balance += amount;
}

void withdraw(BankAccount& account, double amount) {
    if (account.balance >= amount) {
        account.balance -= amount;
    } else {
        cout << "Insufficient funds!" << endl;
    }
}

double calculateInterest(BankAccount& account, double interestRate) {
    return account.balance * interestRate / 100.0;
}

void displayAccountInfo(const BankAccount& account) {
    cout << "Account Number: " << account.accountNumber << endl;
    cout << "Balance: $" << account.balance << endl;
}

int main() {
    vector<BankAccount> accounts = {
        {"123456", 1000.0},
        {"789012", 500.0}
    };

    for (auto& account : accounts) {
        deposit(account, 500.0);
        withdraw(account, 200.0);
        double interest = calculateInterest(account, 2.0);
        displayAccountInfo(account);
        cout << "Interest: $" << interest << endl;
        cout << endl;
    }

    return 0;
}