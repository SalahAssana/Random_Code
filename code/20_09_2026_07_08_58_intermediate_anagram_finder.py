import itertools
import collections

def find_anagrams(word):
    """
    Find all possible anagrams for a given word.

    :param word: The input word to generate anagrams from.
    :return: A list of all possible anagrams.
    """
    # Create a dictionary to store the frequency of each character in the word
    char_freq = collections.defaultdict(int)
    for char in word:
        char_freq[char] += 1

    # Generate all possible permutations of the characters
    permutations = itertools.permutations(word, len(word))

    # Filter out the anagrams that do not have the same frequency as the original word
    anagrams = ["".join(p) for p in permutations if collections.Counter("".join(p)) == char_freq]

    return anagrams

if __name__ == '__main__':
    input_word = "listen"
    print(f"Anagrams of '{input_word}': {find_anagrams(input_word)}")