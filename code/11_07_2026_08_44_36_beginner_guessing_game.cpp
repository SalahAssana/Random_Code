#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Set the seed for random number generation
    srand(time(0));

    // Generate a random number between 1 and 100
    int targetNumber = rand() % 100 + 1;

    // Initialize the player's guess
    int guess;
    bool won = false;

    while (!won) {
        // Ask the player to input their guess
        std::cout << "Guess a number between 1 and 100: ";
        std::cin >> guess;

        // Check if the player's guess is correct
        if (guess == targetNumber) {
            std::cout << "Congratulations, you won! The target number was indeed " << targetNumber << ".\n";
            won = true;
        }
        else if (guess < targetNumber) {
            std::cout << "Too low! Try again.\n";
        }
        else {
            std::cout << "Too high! Try again.\n";
        }
    }

    return 0;
}