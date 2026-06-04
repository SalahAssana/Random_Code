#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Define a struct to represent a conversation step
struct ConversationStep {
    string prompt;
    vector<string> responses;
};

// Function to handle user input and respond accordingly
void chatbotConversationalFlow(map<int, ConversationStep>& steps) {
    int choice = 0;
    cout << "Welcome to the chatbot! Please choose from the following options:" << endl;

    // Print the conversation flow
    for (auto& step : steps) {
        cout << step.first << ". " << step.second.prompt << endl;
    }

    while (true) {
        cin >> choice;

        if (steps.find(choice) != steps.end()) {
            auto& currentStep = steps[choice];
            cout << currentStep.prompt << endl;

            // Get the user's response
            string userResponse;
            cout << "Type your response: ";
            getline(cin, userResponse);

            // Check if the user's response is in the allowed responses
            for (auto& response : currentStep.responses) {
                if (userResponse == response) {
                    cout << "Great choice! Let's move forward." << endl;
                    break; // Exit the loop and continue the conversation flow
                }
            }

            // If no matching response, end the conversation
            else {
                cout << "I didn't understand that. Our conversation has ended." << endl;
                return;
            }
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    // Define the conversation flow as a map of ConversationStep structs
    map<int, ConversationStep> chatbotFlow = {
        {1, {"What's your name?", {"John", "Jane", "Bob"}}},
        {2, {"How are you?", {"I'm good", "I'm not good", "It's complicated"}}},
        {3, {"What do you want to talk about?", {"The weather", "Holidays", "Food"}}}
    };

    // Start the chatbot conversational flow
    chatbotConversationalFlow(chatbotFlow);

    return 0;
}
