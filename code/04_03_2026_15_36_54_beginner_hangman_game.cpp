#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

const int WORD_LENGTH = 7;
const string HANGMAN_PIC[] = {"_ _ _ _ _ _ _,","|   |   |   |   |   |   ","|       |   |   |   |   ","|           |   |   |   ","|               |   |   ","|                   |"};

string word = "clouds";
vector<char> guessedLetters;
int incorrectGuesses = 0;

void displayHangman() {
    cout << HANGMAN_PIC[incorrectGuesses] << endl;
}

void guessLetter(char letter) {
    bool correctGuess = false;
    
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (word[i] == tolower(letter)) {
            guessedLetters.push_back(word[i]);
            correctGuess = true;
        }
    }
    
    if (!correctGuess) {
        incorrectGuesses++;
    }
}

void displayWord() {
    for (char letter : word) {
        bool found = false;
        
        for (char g : guessedLetters) {
            if (g == tolower(letter)) {
                cout << letter << " ";
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "_ ";
        }
    }
    
    cout << endl;
}

int main() {
    for (char c : word) {
        guessedLetters.push_back('_');
    }
    
    while (true) {
        displayHangman();
        displayWord();
        
        char guess;
        cout << "Guess a letter: ";
        cin >> guess;
        
        guess = tolower(guess);
        
        if (guess == 'e' || guess == 'q') {
            break;
        }
        
        guessLetter(guess);
    }
    
    return 0;
}