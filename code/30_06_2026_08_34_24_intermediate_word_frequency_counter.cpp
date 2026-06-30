#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Function to count word frequencies
void countWordFrequencies(const string& filename) {
    map<string, int> wordFrequencyMap;
    
    // Open the file for reading
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    
    // Read the file line by line
    string line;
    while (getline(file, line)) {
        vector<string> words = splitLine(line);
        
        // Count word frequencies for each word in the line
        for (const auto& word : words) {
            if (wordFrequencyMap.find(word) == wordFrequencyMap.end()) {
                wordFrequencyMap[word] = 1;
            } else {
                ++(wordFrequencyMap[word]);
            }
        }
    }
    
    // Print the word frequencies
    cout << "Word Frequencies:" << endl;
    for (const auto& pair : wordFrequencyMap) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

// Function to split a line into words
vector<string> splitLine(const string& line) {
    vector<string> words;
    string word;
    
    // Split the line into words using spaces as delimiters
    for (const auto& c : line) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    
    // Add the last word to the list of words
    if (!word.empty()) {
        words.push_back(word);
    }
    
    return words;
}

int main() {
    string filename = "input.txt";  // Replace with your file name
    
    countWordFrequencies(filename);
    
    return 0;
}