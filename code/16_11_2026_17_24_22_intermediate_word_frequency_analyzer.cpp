#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct WordFrequency {
    string word;
    int frequency;
};

bool compareWordFrequencies(const WordFrequency& a, const WordFrequency& b) {
    return a.frequency > b.frequency;
}

void calculateWordFrequencies(map<string, int>& wordCounts, ifstream& file) {
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string word;
        while (ss >> word) {
            ++wordCounts[word];
        }
    }
}

vector<WordFrequency> sortWordFrequencies(const map<string, int>& wordCounts) {
    vector<WordFrequency> frequencies(wordCounts.begin(), wordCounts.end());
    sort(frequencies.begin(), frequencies.end(), compareWordFrequencies);
    return frequencies;
}

int main() {
    ifstream file("input.txt");
    if (!file) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    map<string, int> wordCounts;
    calculateWordFrequencies(wordCounts, file);

    vector<WordFrequency> frequencies = sortWordFrequencies(wordCounts);

    for (const auto& frequency : frequencies) {
        cout << frequency.word << ": " << frequency.frequency << endl;
    }

    return 0;
}