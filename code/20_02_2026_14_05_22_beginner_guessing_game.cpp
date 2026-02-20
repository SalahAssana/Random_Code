#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random number between 1 and 100
    int targetNumber = rand() % 101;

    // Initialize the number of guesses
    int numberOfGuesses = 0;

    // Initialize the user's guess to -1 (invalid)
    int userGuess = -1;

    while (userGuess != targetNumber) {
        // Ask the user for their guess
        std::cout << "Guess a number between 1 and 100: ";
        std::cin >> userGuess;

        // Increment the number of guesses
        numberOfGuesses++;

        // Check if the user's guess is too high or too low
        if (userGuess > targetNumber) {
            std::cout << "Too high! Try again.\n";
        } else if (userGuess < targetNumber) {
            std::cout << "Too low! Try again.\n";
        }
    }

    // Congratulate the user on guessing correctly
    std::cout << "Congratulations, you guessed it in " << numberOfGuesses << " guesses!\n";

    return 0;
}