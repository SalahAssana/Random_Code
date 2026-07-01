#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Word {
    string word;
    vector<char> guessed;
};

void displayWord(Word& w) {
    for (char c : w.word) {
        if (find(w.guessed.begin(), w.guessed.end(), c) != w.guessed.end()) {
            cout << c << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

void guessLetter(Word& w, char letter) {
    int correct = 0;
    for (int i = 0; i < w.word.length(); i++) {
        if (w.word[i] == letter) {
            w.guessed.push_back(letter);
            correct++;
        }
    }
    if (correct == 0) {
        cout << "Incorrect guess. Try again." << endl;
    } else {
        cout << "Correct! You got " << correct << " letters right." << endl;
    }
}

void playGame() {
    Word word = {"hangman", vector<char>()};
    int attempts = 6;
    while (attempts > 0) {
        displayWord(word);
        char letter;
        cout << "Guess a letter: ";
        cin >> letter;
        guessLetter(word, letter);
        if (word.guessed.size() == word.word.length()) {
            cout << "Congratulations! You won!" << endl;
            return;
        }
    }
    cout << "Game over. The word was " << word.word << "." << endl;
}

int main() {
    playGame();
    return 0;
}