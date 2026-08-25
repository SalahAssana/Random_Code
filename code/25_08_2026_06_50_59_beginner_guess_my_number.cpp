#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed the random number generator
    srand(time(0));

    int randomNumber = rand() % 100 + 1; // Generate a random number between 1 and 100

    int guess;
    int attempts = 0;

    std::cout << "Guess My Number! (Between 1 and 100)" << std::endl;

    while (true) {
        std::cout << "Enter your guess: ";
        std::cin >> guess;

        attempts++;

        if (guess < randomNumber) {
            std::cout << "Too low, try again!" << std::endl;
        } else if (guess > randomNumber) {
            std::cout << "Too high, try again!" << std::endl;
        } else {
            std::cout << "Congratulations! You guessed it in " << attempts << " attempts." << std::endl;
            break;
        }
    }

    return 0;
}