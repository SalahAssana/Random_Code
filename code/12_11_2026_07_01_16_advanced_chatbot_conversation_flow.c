#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to represent a node in the conversation flowchart
typedef struct {
    char* question;
    char** responses;
    int numResponses;
} Node;

// Define a struct to represent the chatbot's current state
typedef struct {
    Node* currentNode;
    int currentState;
} ChatbotState;

// Function to handle user input and update the chatbot's state
void processInput(ChatbotState* state, char* userInput) {
    // Find the next node in the flowchart based on the user's response
    for (int i = 0; i < state->currentNode->numResponses; i++) {
        if (strcmp(userInput, state->currentNode->responses[i]) == 0) {
            state->currentState++;
            return;
        }
    }

    // If no matching response was found, stay in the same state
    printf("Invalid input. Please try again.\n");
}

// Function to update the chatbot's state based on the current node's next state
void advanceState(ChatbotState* state) {
    Node* current = state->currentNode;
    if (state->currentState < current->numResponses) {
        state->currentNode = current->responses[state->currentState];
        state->currentState++;
    } else {
        // If we've reached the end of the flowchart, start over
        state->currentState = 0;
        state->currentNode = current;
    }
}

// Function to display the chatbot's response for a given node
void displayResponse(Node* node) {
    printf("Chatbot: %s\n", node->question);
    for (int i = 0; i < node->numResponses; i++) {
        printf("%d. %s\n", i + 1, node->responses[i]);
    }
}

// Function to initialize the chatbot's state and start the conversation
void startConversation(ChatbotState* state) {
    state->currentNode = NULL;
    state->currentState = 0;

    // Define the flowchart nodes
    Node nodes[] = {
        {"What's your name?", new char*[3], 3},
        {"How are you?", new char*[2], 2},
        {"I'm feeling great!", new char*[1], 1}
    };

    state->currentNode = &nodes[0];
}

int main() {
    // Initialize the chatbot's state
    ChatbotState state;
    startConversation(&state);

    while (1) {
        // Display the current node and get user input
        displayResponse(state.currentNode);
        char userInput[256];
        printf("Enter your response: ");
        fgets(userInput, sizeof(userInput), stdin);

        // Process the user's input and update the chatbot's state
        processInput(&state, userInput);

        // Advance to the next node in the flowchart
        advanceState(&state);
    }

    return 0;
}