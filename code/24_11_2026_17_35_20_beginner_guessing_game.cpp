#include <iostream>
using namespace std;

int main() {
    // Set a random number for the user to guess
    int secretNumber = 42;
    
    // Initialize the number of attempts
    int attempts = 0;
    
    cout << "Welcome to the Guessing Game!" << endl;
    cout << "You have to guess a secret number." << endl;
    
    while (true) {
        // Ask the user for their guess
        int guess;
        cout << "Enter your guess: ";
        cin >> guess;
        
        attempts++;
        
        if (guess == secretNumber) {
            cout << " Congratulations! You guessed it in " << attempts << " attempts." << endl;
            break;
        } else if (guess > secretNumber) {
            cout << "Too high. Try again!" << endl;
        } else {
            cout << "Too low. Try again!" << endl;
        }
    }
    
    return 0;
}