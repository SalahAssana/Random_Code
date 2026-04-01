#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    // Seed random number generator
    srand(time(0));

    // Generate a random number between 1 and 100
    int targetNumber = rand() % 101;

    std::cout << "Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n";
    std::cout << "Try to guess it. You have 6 chances.\n";

    for (int i = 0; i < 6; i++) {
        int userGuess;
        std::cout << "Enter your guess: ";
        std::cin >> userGuess;

        if (userGuess == targetNumber) {
            std::cout << " Congratulations! You guessed the number.\n";
            return 0;
        } else if (userGuess < targetNumber) {
            std::cout << "Your guess is too low. Try again!\n";
        } else {
            std::cout << "Your guess is too high. Try again!\n";
        }
    }

    std::cout << "Sorry, you didn't guess the number. It was " << targetNumber << ". Better luck next time.\n";
    return 0;
}