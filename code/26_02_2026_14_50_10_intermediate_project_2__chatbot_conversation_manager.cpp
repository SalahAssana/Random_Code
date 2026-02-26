#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Chatbot response types
enum class ResponseType {
    GREETING,
    INFORMATIVE,
    HELP,
    GOODBYE
};

// Chatbot conversation manager struct
struct ConversationManager {
    vector<string> greetings;
    vector<string> informativeResponses;
    vector<string> helpMessages;
    vector<string> goodbyes;

    // Constructor to initialize chatbot responses
    ConversationManager() {
        greetings = {"Hello!", "Hi!", "Hey!"};
        informativeResponses = {"I'm a chatbot, here to assist you.", 
                                "I can answer your questions and provide information."};
        helpMessages = {"You can ask me any question or give me a command to get started.", 
                        "Just type what's on your mind, and I'll do my best to respond!"};
        goodbyes = {"Goodbye!", "See you later!", "Thanks for chatting with me!"};
    }

    // Method to generate chatbot response
    string generateResponse(string userInput) {
        if (greetings.size() > 0 && find(greetings.begin(), greetings.end(), userInput) != greetings.end()) {
            return getRandomElement(informativeResponses);
        } else if (informativeResponses.size() > 0 && find(userInput, 0, userInput.size(), userInput) != string::npos) {
            return getRandomElement(helpMessages);
        } else if (find(helpMessages.begin(), helpMessages.end(), userInput) != helpMessages.end()) {
            return getRandomElement(goodbyes);
        }
        return "I didn't understand that. Please try again.";
    }

    // Helper method to get a random element from a vector
    string getRandomElement(vector<string> vec) {
        int index = rand() % vec.size();
        return vec[index];
    }
};

int main() {
    ConversationManager chatbot;

    srand(time(0)); // seed for random number generation

    cout << "Welcome to the chatbot conversation manager!" << endl;
    while (true) {
        string userInput;
        cout << "Enter your message: ";
        getline(cin, userInput);

        if (userInput == "quit") {
            break;
        }

        string response = chatbot.generateResponse(userInput);
        cout << "Chatbot: " << response << endl;
    }

    return 0;
}