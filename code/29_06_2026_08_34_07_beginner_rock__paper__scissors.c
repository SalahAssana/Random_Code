#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int userChoice;
    int computerChoice;

    srand(time(NULL)); // seed for random number generation

    printf("Enter your choice (0: Rock, 1: Paper, 2: Scissors): ");
    scanf("%d", &userChoice);

    computerChoice = rand() % 3; // generate a random number between 0 and 2

    switch(userChoice) {
        case 0:
            printf("You chose Rock.\n");
            break;
        case 1:
            printf("You chose Paper.\n");
            break;
        case 2:
            printf("You chose Scissors.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 0 and 2.\n");
            return 1; // exit the program with an error code
    }

    switch(computerChoice) {
        case 0:
            printf("Computer chose Rock.\n");
            break;
        case 1:
            printf("Computer chose Paper.\n");
            break;
        case 2:
            printf("Computer chose Scissors.\n");
            break;
    }

    // determine the winner
    if ((userChoice == 0 && computerChoice == 2) || (userChoice == 1 && computerChoice == 0) || (userChoice == 2 && computerChoice == 1)) {
        printf("You win!\n");
    } else if ((userChoice == 0 && computerChoice == 1) || (userChoice == 1 && computerChoice == 2) || (userChoice == 2 && computerChoice == 0)) {
        printf("Computer wins.\n");
    } else {
        printf("It's a tie!\n");
    }

    return 0;
}