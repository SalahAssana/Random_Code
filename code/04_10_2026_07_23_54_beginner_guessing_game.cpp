#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Define range for random number generation
    const int MIN = 1;
    const int MAX = 100;

    // Generate a random number within the range
    const int NUMBER_TO_GUESS = rand() % (MAX - MIN + 1) + MIN;

    // Initialize attempts counter
    int attempts = 0;

    // Game loop: ask user to guess until correct or max attempts reached
    while (true) {
        // Ask user for their guess
        std::cout << "Guess a number between " << MIN << " and " << MAX << ": ";
        int userGuess;
        std::cin >> userGuess;

        // Increment attempts counter
        attempts++;

        // Check if user guessed correctly
        if (userGuess == NUMBER_TO_GUESS) {
            // User guessed correctly, print result and exit game loop
            std::cout << "Congratulations! You guessed the number in " << attempts << " attempts." << std::endl;
            break;
        } else if (attempts >= 5) {
            // Max attempts reached, user lost
            std::cout << "Sorry, you didn't guess the number. The number was " << NUMBER_TO_GUESS << "." << std::endl;
            break;
        }
    }

    return 0;
}