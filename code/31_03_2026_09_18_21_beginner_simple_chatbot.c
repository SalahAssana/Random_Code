#include <stdio.h>

int main() {
    // Initialize variables for chatbot
    char userInput[100];
    char response[100];

    int i = 0;

    printf("Welcome to Simple Chatbot! Type 'hello' to start a conversation.\n");

    while (1) {
        // Get user input
        printf("You: ");
        fgets(userInput, sizeof(userInput), stdin);

        // Process user input and generate response
        if (strcmp(userInput, "hello\n") == 0) {
            strcpy(response, "Hello! I'm happy to chat with you.\n");
        } else if (strcmp(userInput, "goodbye\n") == 0) {
            strcpy(response, "It was nice talking to you. Goodbye!\n");
        } else if (strcmp(userInput, "help\n") == 0) {
            strcpy(response, "I can understand 'hello', 'goodbye', and 'help'. Try those commands.\n");
        } else {
            strcpy(response, "I didn't quite catch that. Try again?\n");
        }

        // Display response
        printf("Chatbot: %s", response);

        i++;
        if (i > 3) {
            break;
        }
    }

    return 0;
}