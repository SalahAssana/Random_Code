#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random choice for computer
int getComputerChoice() {
    return rand() % 3;
}

// Function to determine winner based on user and computer choices
char determineWinner(int userChoice, int computerChoice) {
    if (userChoice == computerChoice)
        return 'T'; // Tie
    else if ((userChoice == 0 && computerChoice == 2) ||
             (userChoice == 1 && computerChoice == 0) ||
             (userChoice == 2 && computerChoice == 1))
        return 'U'; // User wins
    else
        return 'C'; // Computer wins
}

int main() {
    srand(time(NULL)); // Initialize random seed

    int userChoice;
    printf("Enter your choice (0 for Rock, 1 for Paper, 2 for Scissors): ");
    scanf("%d", &userChoice);

    int computerChoice = getComputerChoice();
    char winner = determineWinner(userChoice, computerChoice);

    printf("\nComputer chose: %s\n", (computerChoice == 0) ? "Rock" : ((computerChoice == 1) ? "Paper" : "Scissors"));
    if (winner == 'T')
        printf("It's a tie!");
    else if (winner == 'U')
        printf("You win!");
    else
        printf("Computer wins!");

    return 0;
}