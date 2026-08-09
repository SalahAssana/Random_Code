#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class StateMachine {
public:
    enum class States { START, GREETING, QUESTION, ANSWER, END };

    void setState(States state) {
        current_state = state;
    }

    void processInput(const string& input) {
        switch (current_state) {
            case States::START:
                if (input == "start") {
                    setState(States::GREETING);
                    cout << "Hello! I'm happy to chat with you." << endl;
                } else {
                    setState(States::END);
                    cout << "Invalid input. Goodbye!" << endl;
                }
                break;
            case States::GREETING:
                if (input == "ask") {
                    setState(States::QUESTION);
                    cout << "What's on your mind?" << endl;
                } else {
                    setState(States::END);
                    cout << "Invalid input. Goodbye!" << endl;
                }
                break;
            case States::QUESTION:
                if (input == "thanks" || input == "thank you") {
                    setState(States::ANSWER);
                    cout << "You're welcome! It was nice chatting with you." << endl;
                } else if (input == "quit" || input == "exit") {
                    setState(States::END);
                    cout << "Goodbye!" << endl;
                } else {
                    setState(States::QUESTION);
                    cout << "I didn't understand that. Please try again." << endl;
                }
                break;
            case States::ANSWER:
                if (input == "quit" || input == "exit") {
                    setState(States::END);
                    cout << "Goodbye!" << endl;
                } else {
                    setState(States::QUESTION);
                    cout << "I didn't understand that. Please try again." << endl;
                }
                break;
            case States::END:
                // do nothing
                break;
        }
    }

private:
    States current_state = States::START;
};

int main() {
    StateMachine state_machine;

    while (true) {
        string input;
        cout << "Chatbot: ";
        getline(cin, input);

        state_machine.processInput(input);
    }

    return 0;
}