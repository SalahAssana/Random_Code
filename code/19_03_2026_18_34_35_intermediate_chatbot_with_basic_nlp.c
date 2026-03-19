#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 256
#define MAX_RESPONSE 128
#define MAX_KEYWORDS 10
#define KEYWORD_MAX_LENGTH 20

typedef struct {
    char* keyword;
    char* response;
} Keyword;

// Function to tokenize input text into individual words
void tokenize(char* input, char** tokens) {
    int token_count = 0;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == ' ') {
            token_count++;
            input[i] = '\0';
        }
    }
    tokens[0] = input;
    token_count++;
}

// Function to perform stemming on individual words
void stem(char** tokens, int token_count) {
    for (int i = 0; i < token_count; i++) {
        // Simple porter stemming algorithm
        if (strlen(tokens[i]) > 3 && tokens[i][strlen(tokens[i]) - 1] == 's' &&
            strlen(tokens[i]) - 1 >= 2) {
            int j;
            for (j = strlen(tokens[i]) - 1; j >= 2 && isalpha(tokens[i][j]); j--) {
                if (!isupper(tokens[i][j])) {
                    break;
                }
            }
            tokens[i][j] = '\0';
        }
    }
}

// Function to match user input with keyword responses
char* respond(char* input, Keyword* keywords) {
    char** tokens = (char**)malloc(MAX_KEYWORDS * sizeof(char*));
    int token_count = 0;
    tokenize(input, tokens);
    stem(tokens, token_count);

    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (tokens[i] && strcmp(tokens[i], keywords[i].keyword) == 0) {
            return keywords[i].response;
        }
    }

    free(tokens);
    return "I didn't understand that. Try again!";
}

int main() {
    Keyword keywords[MAX_KEYWORDS] = {
        {"hello", "Hi there! How are you?" },
        {"thanks", "You're welcome!" },
        {"help", "What do you need help with?" },
        {"exit", "Goodbye!" }
    };

    char input[MAX_INPUT];
    printf("Chatbot: Hi, what's up? Type 'hello', 'thanks', 'help' or 'exit'\n");
    fgets(input, MAX_INPUT, stdin);

    char* response = respond(input, keywords);
    printf("%s\n", response);

    return 0;
}