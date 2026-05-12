#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to represent a bank account
typedef struct {
    int id;
    char name[20];
    float balance;
} Account;

// Function to create a new account
Account* createAccount(int id, const char* name, float initialBalance) {
    Account* account = (Account*)malloc(sizeof(Account));
    account->id = id;
    strcpy(account->name, name);
    account->balance = initialBalance;
    return account;
}

// Function to display an account's details
void displayAccount(Account* account) {
    printf("Account ID: %d\n", account->id);
    printf("Account Holder: %s\n", account->name);
    printf("Balance: %.2f\n", account->balance);
}

// Function to deposit money into an account
void deposit(Account* account, float amount) {
    account->balance += amount;
}

// Function to withdraw money from an account
void withdraw(Account* account, float amount) {
    if (account->balance >= amount) {
        account->balance -= amount;
    } else {
        printf("Insufficient funds!\n");
    }
}

// Function to transfer money between accounts
void transfer(Account* sender, Account* receiver, float amount) {
    withdraw(sender, amount);
    deposit(receiver, amount);
}

// Function to authenticate a user and return their account
Account* authenticate(int id, const char* password, Account* accounts[], int numAccounts) {
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i]->id == id && strcmp(accounts[i]->name, "JohnDoe") == 0) { // Hardcoded user name
            return accounts[i];
        }
    }
    return NULL;
}

// Main function to test the banking system
int main() {
    Account* accounts[3];

    // Create three accounts
    accounts[0] = createAccount(1, "JohnDoe", 1000.00);
    accounts[1] = createAccount(2, "JaneSmith", 500.00);
    accounts[2] = createAccount(3, "BobJohnson", 2000.00);

    // Authenticate and display account details
    Account* selectedAccount = authenticate(1, "password123", accounts, 3);
    if (selectedAccount) {
        displayAccount(selectedAccount);
        deposit(selectedAccount, 500.00);
        withdraw(selectedAccount, 300.00);
        transfer(accounts[0], accounts[1], 100.00);
        printf("New balance: %.2f\n", selectedAccount->balance);
    } else {
        printf("Invalid credentials!\n");
    }

    // Free memory allocated for accounts
    for (int i = 0; i < 3; i++) {
        free(accounts[i]);
    }

    return 0;
}