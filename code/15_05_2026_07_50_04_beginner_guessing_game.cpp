#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    // Initialize random seed
    srand(time(0));

    int numToGuess = rand() % 100 + 1; // Random number between 1 and 100

    std::cout << "Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n";
    for (int tries = 0; ; ++tries) {
        int guess;
        std::cout << "\nEnter your guess: ";
        std::cin >> guess;

        if (guess > numToGuess) {
            std::cout << "Too high! Try again.\n";
        } else if (guess < numToGuess) {
            std::cout << "Too low! Try again.\n";
        } else {
            std::cout << "\n Congratulations, you guessed the number in " << tries + 1 << " tries!\n";
            break;
        }
    }

    return 0;
}