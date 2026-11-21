#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Define a struct to represent a word in the language processing task
typedef struct {
    char* word;
    int frequency;
} Word;

// Function to tokenize a sentence into words
Word** tokenize(char* sentence) {
    // Split the sentence by spaces and store the words in an array of pointers
    char* token = strtok(sentence, " ");
    int numTokens = 0;
    Word** wordArray = (Word**)malloc(sizeof(Word*) * 100);
    while(token != NULL) {
        wordArray[numTokens] = (Word*)malloc(sizeof(Word));
        wordArray[numTokens]->word = (char*)malloc(strlen(token) + 1);
        strcpy(wordArray[numTokens]->word, token);
        wordArray[numTokens]->frequency = 0;
        numTokens++;
        token = strtok(NULL, " ");
    }
    return wordArray;
}

// Function to count the frequency of each word in a sentence
void countWordFrequencies(Word** words, int numWords) {
    // Count the frequency of each word and store it in the Word struct
    for(int i = 0; i < numWords; i++) {
        int j;
        for(j = 0; j < i; j++) {
            if(strcmp(words[i]->word, words[j]->word) == 0) {
                break;
            }
        }
        if(j != i) {
            words[i]->frequency = 1;
        } else {
            words[i]->frequency++;
        }
    }
}

// Function to print the frequency of each word
void printWordFrequencies(Word** words, int numWords) {
    // Print the frequency of each word
    for(int i = 0; i < numWords; i++) {
        printf("%s: %d\n", words[i]->word, words[i]->frequency);
    }
}

int main() {
    char* sentence = "This is a sample sentence. This sentence is just a sample.";
    int numWords;
    Word** words;

    // Tokenize the sentence into words
    words = tokenize(sentence);
    numWords = 0;
    for(int i = 0; i < 100; i++) {
        if(words[i] != NULL) {
            numWords++;
        } else {
            break;
        }
    }

    // Count the frequency of each word in the sentence
    countWordFrequencies(words, numWords);

    // Print the frequency of each word
    printWordFrequencies(words, numWords);

    return 0;
}