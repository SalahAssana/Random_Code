#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(0));  // seed random number generator
    int numberToGuess = rand() % 100 + 1;  // generate a random number between 1 and 100
    int attempts = 0;
    
    cout << "Welcome to the Guessing Game! I'm thinking of a number between 1 and 100." << endl;
    cout << "You have to guess it. Good luck!" << endl;
    
    while (true) {
        int guess;
        cout << "Enter your guess: ";
        cin >> guess;
        
        attempts++;
        
        if (guess < numberToGuess) {
            cout << "Too low! Try again." << endl;
        } else if (guess > numberToGuess) {
            cout << "Too high! Try again." << endl;
        } else {
            cout << " Congratulations! You guessed the number in " << attempts << " attempts." << endl;
            break;
        }
    }
    
    return 0;
}