#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Function to find all anagrams of a given word from a list of words
std::vector<std::string> findAnagrams(const std::string& word, const std::vector<std::string>& dictionary) {
    // Create a vector to store the anagrams
    std::vector<std::string> anagrams;

    // Sort the characters in the given word
    std::string sortedWord = word;
    std::sort(sortedWord.begin(), sortedWord.end());

    // Iterate over each word in the dictionary
    for (const auto& dictWord : dictionary) {
        // Create a copy of the current dictionary word
        std::string dictCopy = dictWord;

        // Sort the characters in the current dictionary word
        std::sort(dictCopy.begin(), dictCopy.end());

        // Check if the sorted dictionary word is equal to the sorted given word
        if (dictCopy == sortedWord) {
            anagrams.push_back(dictWord);
        }
    }

    return anagrams;
}

int main() {
    // Synthetic data: Create a list of words
    std::vector<std::string> dictionary = {"cat", "act", "dog", "god", "hello", "world", "listen", "silent"};

    // Word for which we want to find all anagrams
    const std::string word = "listen";

    // Find and print the anagrams of the given word
    std::vector<std::string> anagrams = findAnagrams(word, dictionary);

    if (!anagrams.empty()) {
        std::cout << "Anagrams of '" << word << "': ";
        for (const auto& anagram : anagrams) {
            std::cout << anagram << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "'" << word << "' has no anagrams in the dictionary." << std::endl;
    }

    return 0;
}