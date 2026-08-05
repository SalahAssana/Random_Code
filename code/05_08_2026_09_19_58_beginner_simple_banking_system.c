#include <stdio.h>
#include <stdlib.h>

// Define structure for Bank Account
typedef struct {
    float balance;
} BankAccount;

// Function to create a new bank account
BankAccount* create_account() {
    BankAccount* account = (BankAccount*)malloc(sizeof(BankAccount));
    account->balance = 0.0;
    return account;
}

// Function to deposit money into the account
void deposit(BankAccount* account, float amount) {
    account->balance += amount;
    printf("Deposited $%.2f. New balance: $%.2f\n", amount, account->balance);
}

// Function to withdraw money from the account
void withdraw(BankAccount* account, float amount) {
    if (account->balance >= amount) {
        account->balance -= amount;
        printf("Withdrew $%.2f. New balance: $%.2f\n", amount, account->balance);
    } else {
        printf("Insufficient funds!\n");
    }
}

// Function to display the account balance
void display_balance(BankAccount* account) {
    printf("Your current balance is: $%.2f\n", account->balance);
}

int main() {
    BankAccount* account = create_account();

    int choice;
    float amount;

    while (1) {
        printf("Choose an option:\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Check Balance\n");
        printf("4. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                deposit(account, amount);
                break;
            case 2:
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                withdraw(account, amount);
                break;
            case 3:
                display_balance(account);
                break;
            case 4:
                free(account);
                return 0;
            default:
                printf("Invalid choice. Try again!\n");
        }
    }

    return 0;
}