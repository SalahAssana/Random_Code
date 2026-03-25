#include <stdio.h>
#include <stdlib.h>

// Define structure for bank account
typedef struct {
    int account_number;
    float balance;
} BankAccount;

// Function to create new bank account
BankAccount* create_account(int account_number) {
    BankAccount* account = (BankAccount*) malloc(sizeof(BankAccount));
    account->account_number = account_number;
    account->balance = 0.0;
    return account;
}

// Function to deposit money into the account
void deposit(BankAccount* account, float amount) {
    account->balance += amount;
    printf("Deposited $%.2f into account %d. New balance: $%.2f\n", 
           amount, account->account_number, account->balance);
}

// Function to withdraw money from the account
void withdraw(BankAccount* account, float amount) {
    if (amount > account->balance) {
        printf("Insufficient funds in account %d. Current balance: $%.2f\n", 
               account->account_number, account->balance);
    } else {
        account->balance -= amount;
        printf("Withdrawn $%.2f from account %d. New balance: $%.2f\n", 
               amount, account->account_number, account->balance);
    }
}

int main() {
    // Create a new bank account
    BankAccount* account = create_account(12345);

    // Perform some transactions
    deposit(account, 1000.00);
    withdraw(account, 500.00);
    deposit(account, 200.00);
    withdraw(account, 300.00);

    // Free the memory for the bank account
    free(account);

    return 0;
}