#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    // Seed random number generator
    srand(time(0));

    // Generate a random number between 1 and 100
    int secretNumber = rand() % 100 + 1;

    // Initialize attempts counter to 0
    int attempts = 0;

    // Start game loop
    while (true) {
        // Ask user for their guess
        std::cout << "Guess a number between 1 and 100: ";
        int guess;
        std::cin >> guess;

        // Increment attempts counter
        attempts++;

        // Check if the guess is correct
        if (guess == secretNumber) {
            std::cout << "Congratulations! You found the number in " << attempts << " attempts." << std::endl;
            break;
        }
        // Check if the guess is too high or too low
        else if (guess > secretNumber) {
            std::cout << "Too high! Try again." << std::endl;
        } else {
            std::cout << "Too low! Try again." << std::endl;
        }
    }

    return 0;
}