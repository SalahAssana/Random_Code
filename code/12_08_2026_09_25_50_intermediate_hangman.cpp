#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Define a struct to represent a word in Hangman
struct Word {
    char* word;
    int length;
};

// Function to generate a random word from a given array of words
Word* generateRandomWord(char** words, int numWords) {
    // Generate a random index for the word
    srand(time(0));
    int randIndex = rand() % numWords;

    // Allocate memory for the selected word
    Word* selectedWord = new Word;
    selectedWord->word = strcpy(new char[strlen(words[randIndex]) + 1], words[randIndex]);
    selectedWord->length = strlen(selectedWord->word);

    return selectedWord;
}

// Function to display the current state of the word with underscores for unknown letters
void displayWord(Word* word, char** guesses) {
    // Initialize a string to store the displayed word
    char* displayedWord = new char[word->length + 1];
    displayedWord[word->length] = '\0';

    // Iterate over each character in the word
    for (int i = 0; i < word->length; i++) {
        bool foundInGuesses = false;
        for (int j = 0; guesses[j]; j++) {
            if (word->word[i] == guesses[j][0]) {
                displayedWord[i] = word->word[i];
                foundInGuesses = true;
                break;
            }
        }

        // If the character is not guessed, add an underscore
        if (!foundInGuesses) {
            displayedWord[i] = '_';
        }
    }

    // Print the displayed word
    std::cout << "Word: ";
    for (int i = 0; i < word->length; i++) {
        std::cout << displayedWord[i];
    }
    std::cout << std::endl;

    delete[] displayedWord;
}

// Function to check if the game is over based on the number of correct guesses
bool gameOver(Word* word, char** guesses) {
    int correctGuesses = 0;
    for (int i = 0; i < word->length; i++) {
        bool foundInGuesses = false;
        for (int j = 0; guesses[j]; j++) {
            if (word->word[i] == guesses[j][0]) {
                correctGuesses++;
                foundInGuessed = true;
                break;
            }
        }
    }

    // Game over if all letters are guessed or the word is fully displayed
    return correctGuesses == word->length || !strchr(word->word, '_');
}

// Function to play the game
void playGame(Word* word, char** guesses) {
    while (!gameOver(word, guesses)) {
        // Display the current state of the word
        displayWord(word, guesses);

        // Ask for a new guess and add it to the list of guesses
        std::cout << "Enter your next guess: ";
        char input[2];
        std::cin >> input;
        guesses = (char**) realloc(guesses, sizeof(char*) * (strlen(guesses) + 2));
        guesses[strlen(guesses)] = strcpy(new char[strlen(input) + 1], input);
    }

    // Display the final state of the word
    displayWord(word, guesses);

    std::cout << "Congratulations! You won!" << std::endl;
}

int main() {
    // Define an array of words for the game
    char* words[] = {"hello", "world", "hangman", "game", "play"};
    int numWords = sizeof(words) / sizeof(words[0]);

    // Generate a random word from the given array
    Word* selectedWord = generateRandomWord(words, numWords);

    // Initialize an empty list of guesses
    char** guesses = new char*[1];
    guesses[0] = nullptr;

    // Play the game with the generated word and initial guesses
    playGame(selectedWord, guesses);

    // Clean up memory
    delete[] selectedWord->word;
    delete selectedWord;
    for (int i = 0; i < strlen(guesses); i++) {
        delete[] guesses[i];
    }
    free(guesses);

    return 0;
}