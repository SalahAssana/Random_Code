#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONVERSATION 1000
#define MAX_RESPONSE 200

// Define possible user inputs
enum UserInput {
    GREETING,
    GOODBYE,
    HELP,
    UNKNOWN
};

// Define conversation structure
typedef struct {
    enum UserInput input;
    char* response;
} Conversation;

// Initialize conversation dictionary
Conversation conversations[] = {
    {GREETING, "Hello! I'm your chatbot. How can I assist you?"}, // 0
    {GOODBYE, "Goodbye! It was nice chatting with you."},          // 1
    {HELP, "I can help with general knowledge or provide definitions for common terms. What would you like to know?"}, // 2
    {UNKNOWN, "Sorry, I didn't understand that. Please try again."} // 3
};

// Define chatbot functions
void respond(int input) {
    int i;
    for (i = 0; i < MAX_CONVERSATION; i++) {
        if (conversations[i].input == input) {
            printf("%s\n", conversations[i].response);
            return;
        }
    }
}

int main() {
    int choice;
    char response[MAX_RESPONSE];

    while (1) {
        printf("Enter 0 for greeting, 1 for goodbye, 2 for help, or any other number to continue the conversation: ");
        scanf("%d", &choice);

        switch (choice) {
            case GREETING:
                respond(GREETING);
                break;
            case GOODBYE:
                respond(GOODBYE);
                break;
            case HELP:
                respond(HELP);
                break;
            default:
                printf("Please enter a valid option.\n");
                respond(UNKNOWN);
        }
    }

    return 0;
}