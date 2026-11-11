#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nltk.h"
#include "parsing.h"

// Define struct for chatbot's knowledge base
typedef struct {
    char* keyword;
    char* response;
} KBEntry;

// Function to tokenize user input
char** tokenize(char* input) {
    // Use NLTK library to tokenize the input
    NLPTokenizer* tokenizer = nltk_tokenizer();
    char** tokens = nltk_tokenize(tokenizer, input);
    return tokens;
}

// Function to recognize entities in tokenized input
void recognize_entities(char** tokens) {
    // Use parsing library to recognize entities
    ParsingEngine* engine = parsing_engine();
    for (int i = 0; i < strlen(input); i++) {
        char* entity = parsing_recognize(engine, tokens[i]);
        if (entity != NULL) {
            printf("Entity recognized: %s\n", entity);
        }
    }
}

// Function to respond based on recognized entities
void respond(char** tokens) {
    // Use knowledge base to find matching response
    KBEntry* entry = NULL;
    for (int i = 0; i < strlen(input); i++) {
        if (tokens[i] != NULL && strcasecmp(tokens[i], "hello") == 0) {
            entry = &kb_entries[0];
            break;
        }
    }
    if (entry != NULL) {
        printf("Chatbot: %s\n", entry->response);
    } else {
        printf("Chatbot: Sorry, I didn't understand.\n");
    }
}

// Function to handle user input
void handle_input(char* input) {
    char** tokens = tokenize(input);
    recognize_entities(tokens);
    respond(tokens);
    free(tokens);
}

int main() {
    // Initialize knowledge base
    KBEntry kb_entries[] = {
        {"hello", "Hi there!"},
        {"goodbye", "Goodbye for now!"}
    };
    int num_entries = sizeof(kb_entries) / sizeof(KBEntry);

    // Main loop to handle user input
    while (1) {
        printf("Enter a message: ");
        char* input = NULL;
        size_t length = 0;
        getline(&input, &length, stdin);
        handle_input(input);
        free(input);
    }
    return 0;
}