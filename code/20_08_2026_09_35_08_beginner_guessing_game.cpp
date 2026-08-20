#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    // Seed for random number generation
    srand(static_cast<unsigned int>(time(0)));

    // Randomly generate a number between 1 and 100
    int targetNumber = rand() % 101;

    // Initialize the number of attempts
    int attempts = 0;

    // Game loop
    while (true) {
        // Ask the user for their guess
        std::cout << "Guess a number between 1 and 100: ";
        int guess;
        std::cin >> guess;

        // Check if the guess is correct
        if (guess == targetNumber) {
            std::cout << " Congratulations! You guessed it in " << attempts + 1 << " attempts." << std::endl;
            break;
        }
        else if (guess < targetNumber) {
            std::cout << "Too low. Try again!" << std::endl;
        }
        else {
            std::cout << "Too high. Try again!" << std::endl;
        }

        // Increment the number of attempts
        attempts++;
    }

    return 0;
}