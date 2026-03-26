#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(0)); // seed random number generator
    int numberToGuess = rand() % 100 + 1; // generate a random number between 1 and 100

    int guess;
    bool correct = false;

    while (!correct) {
        std::cout << "Guess the number (between 1 and 100): ";
        std::cin >> guess;

        if (guess < 1 || guess > 100) {
            std::cout << "Invalid input. Please enter a number between 1 and 100.\n";
        } else if (guess == numberToGuess) {
            correct = true;
            std::cout << "Congratulations! You guessed the number correctly.\n";
        } else if (guess < numberToGuess) {
            std::cout << "Too low. Try again!\n";
        } else {
            std::cout << "Too high. Try again!\n";
        }
    }

    return 0;
}