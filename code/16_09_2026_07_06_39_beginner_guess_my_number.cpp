#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed random number generator
    srand(time(0));

    // Generate a random number within range [1, 100]
    int secretNumber = rand() % 100 + 1;

    // Initialize the maximum number of attempts
    int maxAttempts = 6;

    // Initialize the current attempt counter
    int attempts = 0;

    // Start game loop
    while (attempts < maxAttempts) {
        // Prompt user to guess a number
        std::cout << "Guess my number between 1 and 100: ";
        
        // Read user's input
        int userGuess;
        std::cin >> userGuess;

        // Check if the user's guess is correct
        if (userGuess == secretNumber) {
            // If correct, print a success message and exit loop
            std::cout << " Congratulations! You guessed my number in " << attempts + 1 << " attempts." << std::endl;
            break;
        } else {
            // If incorrect, print a hint and increment the attempt counter
            if (userGuess < secretNumber) {
                std::cout << "Too low. Try again!" << std::endl;
            } else {
                std::cout << "Too high. Try again!" << std::endl;
            }
            attempts++;
        }
    }

    // If the user exceeds the maximum number of attempts, reveal the correct answer
    if (attempts >= maxAttempts) {
        std::cout << "Sorry, you ran out of attempts! The correct answer was: " << secretNumber << std::endl;
    }

    return 0;
}