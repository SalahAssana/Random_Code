#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    srand(static_cast<unsigned int>(time(0))); // seed random number generator
    int targetNumber = rand() % 100 + 1; // generate a random number between 1 and 100
    
    std::cout << "Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n";
    
    int guess;
    while(true) {
        std::cout << "Guess a number: ";
        std::cin >> guess;
        
        if(guess == targetNumber) {
            std::cout << " Congratulations! You guessed correctly!\n";
            break; // exit the loop when the user guesses correctly
        } else if(guess < targetNumber) {
            std::cout << "Your guess is too low. Try again.\n";
        } else {
            std::cout << "Your guess is too high. Try again.\n";
        }
    }
    
    return 0;
}