#include <stdio.h>
#include <stdlib.h>

// Define a struct to represent a bank account
typedef struct {
    int account_number;
    float balance;
} BankAccount;

// Function to create a new bank account
BankAccount* create_account(int account_number) {
    BankAccount* new_account = (BankAccount*)malloc(sizeof(BankAccount));
    new_account->account_number = account_number;
    new_account->balance = 0.0;
    return new_account;
}

// Function to deposit money into a bank account
void deposit(BankAccount* account, float amount) {
    if (amount > 0) {
        account->balance += amount;
        printf("Deposit of $%.2f made in account %d. New balance: $%.2f\n", 
               amount, account->account_number, account->balance);
    } else {
        printf("Invalid deposit amount. Please try again.\n");
    }
}

// Function to withdraw money from a bank account
void withdraw(BankAccount* account, float amount) {
    if (amount > 0 && account->balance >= amount) {
        account->balance -= amount;
        printf("Withdrawal of $%.2f made in account %d. New balance: $%.2f\n", 
               amount, account->account_number, account->balance);
    } else {
        printf("Invalid withdrawal amount or insufficient funds. Please try again.\n");
    }
}

// Function to display the current balance of a bank account
void show_balance(BankAccount* account) {
    printf("Current balance in account %d: $%.2f\n", 
           account->account_number, account->balance);
}

int main() {
    // Create two bank accounts
    BankAccount* account1 = create_account(1234);
    BankAccount* account2 = create_account(5678);

    // Perform some banking operations
    deposit(account1, 100.0);
    withdraw(account1, 50.0);
    show_balance(account1);

    deposit(account2, 500.0);
    withdraw(account2, 200.0);
    show_balance(account2);

    // Clean up memory
    free(account1);
    free(account2);

    return 0;
}