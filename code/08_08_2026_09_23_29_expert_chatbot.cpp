#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>

// Forward declaration of classes
class State;
class Transition;

// Class representing a state in the chatbot's finite state machine
class State {
public:
    std::string name; // Name of the state
    std::vector<Transition*> transitions; // Transitions from this state

    // Constructor for creating a new state
    State(std::string name) : name(name) {}
};

// Class representing a transition in the chatbot's finite state machine
class Transition {
public:
    State* fromState; // The state that this transition is leaving
    State* toState; // The state that this transition is entering
    std::regex pattern; // Regular expression pattern for the input to trigger this transition

    // Constructor for creating a new transition
    Transition(State* fromState, State* toState, std::string pattern) : fromState(fromState), toState(toState) {
        this->pattern = std::regex(pattern);
    }
};

// Class representing the chatbot itself
class Chatbot {
public:
    State* currentState; // The current state of the chatbot

    // Constructor for creating a new chatbot
    Chatbot() : currentState(nullptr) {}

    // Method to handle user input and transition between states
    void processInput(const std::string& input) {
        for (auto& transition : transitions[currentState->name]) {
            if (transition->pattern.match(input)) {
                // If the pattern matches, transition to the new state
                currentState = transition->toState;
                return;
            }
        }

        // If no matching pattern is found, stay in the current state
    }

private:
    std::unordered_map<std::string, State*> states; // Map of all states and their names
    std::vector<Transition*> transitions; // Vector of all transitions

    // Method to add a new state to the chatbot
    void addState(State* state) {
        states[state->name] = state;
        if (currentState == nullptr) {
            currentState = state;
        }
    }

    // Method to add a transition between two states
    void addTransition(Transition* transition) {
        transitions.push_back(transition);
    }
};

int main() {
    // Create the chatbot and its states
    Chatbot chatbot;

    State* state1 = new State("start");
    State* state2 = new State("greeting");
    State* state3 = new State("farewell");

    // Define the transitions between states
    Transition* transition1 = new Transition(state1, state2, std::regex("^hello.*$"));
    Transition* transition2 = new Transition(state2, state3, std::regex("^goodbye.*$"));

    // Add the states and transitions to the chatbot
    chatbot.addState(state1);
    chatbot.addState(state2);
    chatbot.addState(state3);
    chatbot.addTransition(transition1);
    chatbot.addTransition(transition2);

    // Process user input and transition between states
    while (true) {
        std::cout << "Chatbot: ";
        std::string input;
        std::getline(std::cin, input);
        chatbot.processInput(input);
        if (chatbot.currentState->name == "farewell") {
            break;
        }
    }

    return 0;
}