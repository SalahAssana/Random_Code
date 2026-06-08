#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class StateMachine {
public:
    enum class State { START, GREETING, CONVERSATION, GOODBYE };

    StateMachine() : currentState(State::START) {}

    void setState(State state) {
        this->currentState = state;
    }

    State getCurrentState() const {
        return currentState;
    }

private:
    State currentState;
};

class Chatbot {
public:
    map<string, string> responses;
    vector<string> greetings;
    vector<string> goodbyes;

    Chatbot() : responses({
            {"hello", "Hello! How can I help you today?"},
            {"hi", "Hi! What's on your mind?"}
        }), greetings({"hello", "hi"}), goodbyes({"goodbye", "see you later", "later"}) {}

    string processInput(const string& input) {
        StateMachine stateMachine;

        switch (stateMachine.getCurrentState()) {
            case State::START:
                if (find(greetings.begin(), greetings.end(), input) != greetings.end()) {
                    stateMachine.setState(State::GREETING);
                    return "What's on your mind?";
                } else if (input == "goodbye" || input == "see you later" || input == "later") {
                    stateMachine.setState(State::GOODBYE);
                    return "It was nice chatting with you. Goodbye!";
                } else {
                    stateMachine.setState(State::CONVERSATION);
                    return responses.at(input);
                }
            case State::GREETING:
                if (input == "goodbye" || input == "see you later" || input == "later") {
                    stateMachine.setState(State::GOODBYE);
                    return "It was nice chatting with you. Goodbye!";
                } else {
                    return responses.at(input);
                }
            case State::CONVERSATION:
                if (input == "goodbye" || input == "see you later" || input == "later") {
                    stateMachine.setState(State::GOODBYE);
                    return "It was nice chatting with you. Goodbye!";
                } else {
                    return responses.at(input);
                }
            case State::GOODBYE:
                return "It was nice chatting with you. Goodbye!";
        }
    }

};

int main() {
    Chatbot chatbot;

    string input;
    while (true) {
        cout << "Enter your message: ";
        getline(cin, input);

        string response = chatbot.processInput(input);
        cout << response << endl;
    }

    return 0;
}