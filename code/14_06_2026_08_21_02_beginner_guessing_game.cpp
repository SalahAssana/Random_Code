#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(0)); // seed random number generator

    int answer = rand() % 100 + 1; // generate a random number between 1 and 100
    int guess;
    int attempts = 0;

    std::cout << "Guess the number! (between 1 and 100)\n";

    do {
        std::cin >> guess;
        if (guess < answer) {
            std::cout << "Too low, try again!\n";
        }
        else if (guess > answer) {
            std::cout << "Too high, try again!\n";
        }
        attempts++;
    } while (guess != answer);

    std::cout << "Congratulations! You guessed the number in " << attempts << " attempts.\n";

    return 0;
}