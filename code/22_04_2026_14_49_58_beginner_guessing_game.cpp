#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed random number generator
    srand(time(0));

    int secretNumber = rand() % 100 + 1;
    int maxAttempts = 6;

    std::cout << "Welcome to the Guessing Game! I'm thinking of a number between 1 and 100. You have " << maxAttempts << " attempts to guess it.\n";

    for (int i = 0; i < maxAttempts; i++) {
        int userGuess;
        std::cout << "Enter your guess: ";
        std::cin >> userGuess;

        if (userGuess == secretNumber) {
            std::cout << " Congratulations! You guessed it in " << i + 1 << " attempts.\n";
            return 0;
        } else if (i < maxAttempts - 1) {
            if (userGuess > secretNumber) {
                std::cout << "Too high. Try again!\n";
            } else {
                std::cout << "Too low. Try again!\n";
            }
        } else {
            std::cout << "Game over! The number was " << secretNumber << ". Better luck next time.\n";
            return 1;
        }
    }

    return 0;
}