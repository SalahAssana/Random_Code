#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Sentiment {
    double positive;
    double negative;
};

class Chatbot {
public:
    Chatbot() : responses({"Hello, how are you?", "That's great!", "I'm not sure."}) {}

    string respond(string input) {
        Sentiment sentiment = analyzeSentiment(input);
        return getResponse(sentiment);
    }

private:
    vector<string> responses;

    Sentiment analyzeSentiment(string input) {
        double positiveCount = 0;
        double negativeCount = 0;

        for (char c : input) {
            if (isalpha(c)) {
                string word = "";
                while ((c = getchar()) && isalpha(c)) {
                    word += c;
                }
                if (word.find("happy") != string::npos || word.find("great") != string::npos)
                    positiveCount++;
                else if (word.find("sad") != string::npos || word.find("bad") != string::npos)
                    negativeCount++;
            }
        }

        return Sentiment(positiveCount / input.length(), negativeCount / input.length());
    }

    string getResponse(Sentiment sentiment) {
        if (sentiment.positive > sentiment.negative)
            return responses[0];
        else if (sentiment.positive < sentiment.negative)
            return responses[2];
        else
            return responses[1];
    }
};

int main() {
    Chatbot chatbot;
    ifstream file("chat.txt");
    string line;

    while (getline(file, line)) {
        cout << "User: " << line << endl;
        string response = chatbot.respond(line);
        cout << "Chatbot: " << response << endl;
        cout << endl;
    }

    return 0;
}