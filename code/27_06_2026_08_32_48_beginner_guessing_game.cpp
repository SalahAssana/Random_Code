#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    // Seed the random number generator
    srand(time(0));

    // Generate a random number between 1 and 100
    int numberToGuess = rand() % 100 + 1;

    // Initialize the number of attempts to 0
    int numberOfAttempts = 0;

    // Loop until the user guesses the correct number
    while (true) {
        // Ask the user for their guess
        std::cout << "Guess a number between 1 and 100: ";

        // Read the user's input
        int userGuess;
        std::cin >> userGuess;

        // Increment the number of attempts
        numberOfAttempts++;

        // Check if the user guessed correctly
        if (userGuess == numberToGuess) {
            // If they did, display a success message and exit the loop
            std::cout << "Congratulations! You guessed the correct number in " << numberOfAttempts << " attempts." << std::endl;
            break;
        } else if (userGuess < numberToGuess) {
            // If their guess was too low, provide feedback
            std::cout << "Your guess is too low. Try again!" << std::endl;
        } else {
            // If their guess was too high, provide feedback
            std::cout << "Your guess is too high. Try again!" << std::endl;
        }
    }

    return 0;
}