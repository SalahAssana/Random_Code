#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed random number generator
    srand(time(0));

    // Set range for the randomly generated number
    int min = 1;
    int max = 100;

    // Generate a random number within the range
    int numberToGuess = (rand() % (max - min + 1)) + min;

    // Initialize attempts and print instructions
    int attempts = 0;
    std::cout << "Guess a number between 1 and 100. You have 6 attempts.\n";

    while(attempts < 6) {
        // Get user's guess
        int guess;
        std::cout << "Enter your guess: ";
        std::cin >> guess;

        // Check if the guess is correct or not
        if(guess == numberToGuess) {
            std::cout << "Congratulations! You guessed the number in " << attempts + 1 << " attempts.\n";
            return 0;
        } else if(guess < numberToGuess) {
            std::cout << "Too low. Try again.\n";
        } else {
            std::cout << "Too high. Try again.\n";
        }

        // Increment attempts
        attempts++;
    }

    // If all attempts are used, print a message and exit
    std::cout << "Sorry, you didn't guess the number. The correct answer was " << numberToGuess << ".\n";
    return 0;
}