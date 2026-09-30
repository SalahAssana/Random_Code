#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random number between 1 and 100
    const int secretNumber = rand() % 100 + 1;

    // Initialize guess counter
    int numGuesses = 0;

    // Main game loop
    while (true) {
        // Prompt user for input
        std::cout << "Guess a number between 1 and 100: ";

        // Read user's guess
        int userGuess;
        std::cin >> userGuess;

        // Check if user guessed correctly
        if (userGuess == secretNumber) {
            std::cout << " Congratulations! You guessed the correct number in "
                      << numGuesses + 1 << " attempts." << std::endl;
            break;
        }

        // If not, increment guess counter and prompt again
        numGuesses++;
    }

    return 0;
}