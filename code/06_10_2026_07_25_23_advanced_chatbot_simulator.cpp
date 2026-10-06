#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

class Person {
public:
    string name;
    map<string, vector<string>> knowledgeBase;
    
    Person(string n) : name(n) {}

    void addKnowledge(vector<string> topic, vector<string> facts) {
        knowledgeBase[topic] = facts;
    }

    void respond(string query) {
        for (auto& topic : knowledgeBase) {
            if (topic.first.find(query) != string::npos) {
                cout << "Person: " << name << " knows that ";
                for (string fact : topic.second) {
                    cout << fact << ", ";
                }
                cout << endl;
                return;
            }
        }
        cout << "Person: " << name << " doesn't know that." << endl;
    }
};

class Chatbot {
public:
    Person user;
    Person assistant;

    void startConversation() {
        while (true) {
            string query;
            cout << "User: ";
            getline(cin, query);
            
            user.respond(query);

            if (query == "quit") break;

            string response;
            cout << "Assistant: ";
            generateResponse(query, response);
            cout << response << endl;
        }
    }

private:
    void generateResponse(string query, string& response) {
        // Implement your advanced NLP and decision-making logic here
        // For simplicity, let's just respond with a random sentence
        vector<string> possibleResponses = {"I see what you mean!", "That's an interesting point.", "Let me think about that."};
        int index = rand() % possibleResponses.size();
        response = possibleResponses[index];
    }
};

int main() {
    Chatbot chat;
    
    chat.user.addKnowledge({"computers", "programming"}, {"C++ is a popular programming language.", "Python is also a popular language."});
    chat.assistant.addKnowledge({"computers", "algorithms"}, {"Sorting algorithms are important in computer science."});

    chat.startConversation();

    return 0;
}