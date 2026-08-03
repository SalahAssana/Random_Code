#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Seed random number generator
    srand(time(0));

    // Generate a random number between 1 and 100
    int numberToGuess = rand() % 101 + 1;

    cout << "Welcome to the Guessing Game! I'm thinking of a number between 1 and 100." << endl;
    cout << "You have to guess the number. After each guess, I'll tell you if your guess is higher or lower than my number." << endl;

    int guess = 0;

    do {
        // Ask user for their guess
        cout << "Enter your guess: ";
        cin >> guess;
        cout << "Your guess is: " << guess << endl;

        // Check if the guess is correct
        if (guess == numberToGuess) {
            cout << " Congratulations! You guessed it correctly. The number was indeed " << numberToGuess << "." << endl;
            break;
        } else if (guess < numberToGuess) {
            cout << "Your guess is too low. Try again!" << endl;
        } else {
            cout << "Your guess is too high. Try again!" << endl;
        }
    } while (true);

    return 0;
}