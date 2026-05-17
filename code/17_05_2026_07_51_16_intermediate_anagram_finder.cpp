#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Function to generate all permutations of a string
void permute(string str, int l, int r, vector<string>& result) {
    if (l == r)
        result.push_back(str);
    else {
        for (int i = l; i <= r; i++) {
            swap(str[l], str[i]);
            permute(str, l + 1, r, result);
            swap(str[l], str[i]); // backtrack
        }
    }
}

// Function to find all anagrams of a given word
vector<string> findAnagrams(string word) {
    vector<string> anagrams;
    int n = word.length();
    
    // Generate all permutations of the word
    permute(word, 0, n - 1, anagrams);
    
    return anagrams;
}

int main() {
    string inputWord;
    cout << "Enter a word: ";
    cin >> inputWord;
    
    vector<string> anagrams = findAnagrams(inputWord);
    
    // Print all anagrams
    if (anagrams.size() > 0) {
        cout << "All anagrams for the given word are:\n";
        for (const string& anagram : anagrams) {
            cout << anagram << "\n";
        }
    } else {
        cout << "No anagrams found.\n";
    }
    
    return 0;
}