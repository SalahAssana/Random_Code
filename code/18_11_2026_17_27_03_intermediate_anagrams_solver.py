# Anagrams Solver
from collections import defaultdict

def is_anagram(word1, word2):
    """Check if two words are anagrams"""
    return sorted(word1) == sorted(word2)

def group_anagrams(words):
    """Group words into anagrams"""
    anagrams = defaultdict(list)
    for word in words:
        sorted_word = "".join(sorted(word))
        anagrams[sorted_word].append(word)
    return dict(anagrams)

def print_anagrams(anagrams_dict):
    """Print anagrams"""
    for key, value in anagrams_dict.items():
        if len(value) > 1:  # Anagram group with more than one word
            print(f"Anagrams: {key} - {value}")

if __name__ == '__main__':
    words = ["cat", "dog", "god", "act", "good", "tac"]
    anagrams_dict = group_anagrams(words)
    print_anagrams(anagrams_dict)