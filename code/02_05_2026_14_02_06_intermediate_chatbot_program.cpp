#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Define a struct to represent a chatbot response
struct Response {
    string message;
    int score; // confidence level of the response (1-10)
};

// Function to tokenize user input into words
vector<string> tokenizeInput(const string& input) {
    istringstream iss(input);
    vector<string> tokens;
    string token;
    while (getline(iss, token, ' ')) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to match user query with predefined responses
Response matchQuery(const vector<string>& query) {
    // Define some example responses for a chatbot
    map<vector<string>, Response> responses = {
        {{ "hello", "world" }, { "Hello! How can I help you today?", 8 }},
        {{ "what", "is", "your", "name" }, { "I'm ChatBot, nice to meet you!", 9 }},
        {{ "how", "are", "you" }, { "I'm doing great, thanks for asking!", 7 }}
    };

    // Check if the query matches any predefined response
    Response matchedResponse;
    for (const auto& pair : responses) {
        if (pair.first == query) {
            matchedResponse = pair.second;
            break;
        }
    }

    return matchedResponse;
}

int main() {
    cout << "Welcome to our chatbot! Type your message: ";
    string userInput;
    getline(cin, userInput);

    // Tokenize the user input into words
    vector<string> query = tokenizeInput(userInput);
    Response response = matchQuery(query);

    // Print the chatbot's response
    if (response.score > 0) {
        cout << "Chatbot: " << response.message << endl;
    } else {
        cout << "Sorry, I didn't understand your message." << endl;
    }

    return 0;
}