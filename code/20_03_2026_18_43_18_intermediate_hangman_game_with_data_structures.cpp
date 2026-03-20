#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

// Structure to represent a word
struct Word {
    string text;
    int length;
};

// Function to generate random words of given length
Word* generateRandomWords(int numWords, int length) {
    vector<Word*> words(numWords);
    for (int i = 0; i < numWords; ++i) {
        Word* word = new Word();
        word->text = "";
        for (int j = 0; j < length; ++j) {
            char c = 'a' + rand() % 26;
            word->text += c;
        }
        words[i] = word;
    }
    return &words[0];
}

// Function to play the hangman game
void playHangman(Word* words, int numWords, int length) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, numWords - 1);

    Word* currentWord = &words[dis(gen)];
    string guessedWord(currentWord->length, '-');

    while (true) {
        cout << "Guessed word: " << guessedWord << endl;
        char guess;
        cin >> guess;

        int correctGuesses = 0;
        for (int i = 0; i < currentWord->length; ++i) {
            if (currentWord->text[i] == toupper(guess)) {
                guessedWord[i] = tolower(guess);
                correctGuesses++;
            }
        }

        if (correctGuesses == currentWord->length) {
            cout << "Congratulations! You guessed the word: " << currentWord->text << endl;
            break;
        } else if (correctGuesses == 0) {
            cout << "Try again!" << endl;
        } else {
            cout << "Good job, but not all letters are correct." << endl;
        }
    }
}

int main() {
    int numWords = 5;
    int length = 7;

    Word* words = generateRandomWords(numWords, length);

    playHangman(words, numWords, length);

    return 0;
}