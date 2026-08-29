#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed random number generator
    srand(time(0));

    // Generate random number to be guessed
    int secretNumber = rand() % 100 + 1;

    // Initialize guess counter and maximum attempts
    int guesses = 0;
    const int maxAttempts = 6;

    std::cout << "Welcome to 'Guess My Number'! I'm thinking of a number between 1 and 100.\n";
    std::cout << "You have " << maxAttempts << " chances to guess it.\n";

    while (guesses < maxAttempts) {
        // Get user's guess
        int guess;
        std::cout << "Enter your guess: ";
        std::cin >> guess;

        // Check if the guess is correct
        if (guess == secretNumber) {
            std::cout << "\n Congratulations! You guessed it!\n";
            return 0;
        }
        // Check if the guess is too high or too low
        else if (guess > secretNumber) {
            std::cout << "\n Your guess is too high. Try again.\n";
        } else {
            std::cout << "\n Your guess is too low. Try again.\n";
        }
        // Increment the guess counter
        guesses++;
    }

    // If all attempts are used, reveal the secret number
    std::cout << "\n Sorry, you didn't guess it. The correct answer was " << secretNumber << ".\n";

    return 0;
}