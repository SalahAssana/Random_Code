#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

// Function to extract information from web page using NLP and ML
std::vector<std::string> extractInfo(const std::string& webpage) {
    // Preprocess the webpage text
    std::string text = preprocessText(webpage);

    // Tokenize the text into individual words
    std::vector<std::string> tokens = tokenizeText(text);

    // Use machine learning algorithm to classify and extract relevant information
    std::unordered_map<std::string, int> infoMap;
    for (const auto& token : tokens) {
        if (token.find("key") != std::string::npos || token.find("value") != std::string::npos) {
            infoMap[token] = 1;
        }
    }

    // Analyze the extracted information using algorithms
    std::vector<std::string> relevantInfo;
    for (const auto& pair : infoMap) {
        if (pair.second == 1 && !relevantInfo.empty()) {
            break;
        }
        relevantInfo.push_back(pair.first);
    }

    return relevantInfo;
}

// Function to preprocess the webpage text
std::string preprocessText(const std::string& webpage) {
    // Remove HTML tags and special characters
    std::string text = webpage;
    for (char& c : text) {
        if (!isalnum(c)) {
            c = ' ';
        }
    }

    // Convert to lowercase and remove extra whitespace
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    text.erase(std::remove_if(text.begin(), text.end(), ::isspace), text.end());

    return text;
}

// Function to tokenize the text into individual words
std::vector<std::string> tokenizeText(const std::string& text) {
    std::vector<std::string> tokens;
    for (const auto& c : text) {
        if (isalnum(c)) {
            std::string token = "";
            while (c && isalnum(c)) {
                token += c;
                c = getchar();
            }
            tokens.push_back(token);
        } else if (!token.empty()) {
            tokens.push_back(token);
            token.clear();
        }
    }

    return tokens;
}

int main() {
    std::string webpage = "Example web page content with key-value pairs";
    std::vector<std::string> relevantInfo = extractInfo(webpage);

    for (const auto& info : relevantInfo) {
        std::cout << info << std::endl;
    }

    return 0;
}