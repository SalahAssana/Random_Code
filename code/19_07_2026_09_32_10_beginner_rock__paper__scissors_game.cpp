#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(0)); // seed random number generator
    int choice1, choice2; // user choices (rock = 0, paper = 1, scissors = 2)
    char result[4]; // string to hold game result

    std::cout << "Enter your choice (0 for rock, 1 for paper, 2 for scissors): ";
    std::cin >> choice1;

    choice2 = rand() % 3; // computer's random choice
    switch(choice2) {
        case 0:
            std::cout << "Computer chose: Rock\n";
            break;
        case 1:
            std::cout << "Computer chose: Paper\n";
            break;
        case 2:
            std::cout << "Computer chose: Scissors\n";
            break;
    }

    if((choice1 == 0 && choice2 == 2) || (choice1 == 1 && choice2 == 0) || (choice1 == 2 && choice2 == 1)) {
        result[0] = 'W'; // user wins
    } else if(choice1 == choice2) {
        result[0] = 'T'; // tie
    } else {
        result[0] = 'L'; // computer wins
    }

    switch(choice2) {
        case 0:
            strcpy(result + 1, "rock\n");
            break;
        case 1:
            strcpy(result + 1, "paper\n");
            break;
        case 2:
            strcpy(result + 1, "scissors\n");
            break;
    }

    std::cout << "You chose: ";
    switch(choice1) {
        case 0:
            std::cout << "Rock";
            break;
        case 1:
            std::cout << "Paper";
            break;
        case 2:
            std::cout << "Scissors";
            break;
    }
    std::cout << "\nResult: " << result[0] << result + 1;

    return 0;
}