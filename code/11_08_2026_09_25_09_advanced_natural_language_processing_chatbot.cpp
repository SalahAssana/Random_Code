#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

using namespace std;

class Chatbot {
public:
    // Constructor to load training data from file
    Chatbot(const string& filename) : trainingData{} {
        ifstream inputFile(filename);
        if (!inputFile) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string query, response;
            getline(iss, query, ':');
            getline(iss, response);
            trainingData[query] = move(response);
        }
    }

    // Predict the most likely response given a user input
    pair<string, double> predict(const string& userInput) {
        double maxConfidence = 0.0;
        string bestResponse;

        for (const auto& query : trainingData) {
            if (query.first.find(userInput) != string::npos) {
                const string& response = query.second;
                int confidence = jaccardSimilarity(userInput, query.first);
                if (confidence > maxConfidence) {
                    maxConfidence = confidence;
                    bestResponse = response;
                }
            }
        }

        return {bestResponse, maxConfidence};
    }

private:
    map<string, string> trainingData;

    // Calculate Jaccard similarity between two strings
    int jaccardSimilarity(const string& str1, const string& str2) {
        set<char> set1(str1), set2(str2);
        return (set1.size() + set2.size() - *set1.intersection(set2).size()) / 2;
    }
};

int main() {
    Chatbot chatbot("chatbot_training_data.txt");
    string userInput;

    while (true) {
        cout << "Enter your query: ";
        getline(cin, userInput);
        auto response = chatbot.predict(userInput);

        if (!response.first.empty()) {
            cout << "Chatbot: " << response.first << endl;
        } else {
            cout << "Sorry, I didn't understand that." << endl;
        }

        // To exit the loop, enter 'quit'
        if (userInput == "quit") break;
    }

    return 0;
}