#include <stdio.h>
#include <stdlib.h>

// Function to generate random computer choice (0 = Rock, 1 = Paper, 2 = Scissors)
int computerChoice() {
    return rand() % 3;
}

// Function to get user choice (0 = Rock, 1 = Paper, 2 = Scissors)
int getUserChoice() {
    int choice;
    printf("Enter your choice (0 for Rock, 1 for Paper, 2 for Scissors): ");
    scanf("%d", &choice);
    return choice;
}

// Function to determine the winner
void determineWinner(int userChoice, int computerChoice) {
    if(userChoice == computerChoice) {
        printf("It's a tie!\n");
    } else if((userChoice == 0 && computerChoice == 2) || (userChoice == 1 && computerChoice == 0) || (userChoice == 2 && computerChoice == 1)) {
        printf("You win this round! The score is now 1-0.\n");
    } else {
        printf("Computer wins this round! The score is now 1-1.\n");
    }
}

int main() {
    int userWins = 0, computerWins = 0;
    srand(time(NULL));

    while(1) {
        int userChoice = getUserChoice();
        int computerComp = computerChoice();

        printf("Computer chose %s.\n", (computerComp == 0 ? "Rock" : (computerComp == 1 ? "Paper" : "Scissors")));
        printf("You chose %s.\n", (userChoice == 0 ? "Rock" : (userChoice == 1 ? "Paper" : "Scissors")));

        determineWinner(userChoice, computerComp);

        int playAgain;
        printf("Play again? (1 for yes, 0 for no): ");
        scanf("%d", &playAgain);
        if(playAgain == 0) {
            break;
        }
    }

    printf("Game over! The final score is %d-%d.\n", userWins, computerWins);

    return 0;
}