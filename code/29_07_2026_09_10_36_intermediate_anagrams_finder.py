def find_anagrams(word, anagrams=None):
    """
    Recursive function to generate all possible anagrams of a given word.
    
    :param word: The original word
    :param anagrams: A list to store the generated anagrams (default None)
    """
    if anagrams is None:
        anagrams = []
    # Base case: If the length of the word is 1, it's already an anagram
    if len(word) == 1:
        anagrams.append(word)
    else:
        for i in range(len(word)):
            # Generate all possible anagrams by moving each character to the front
            remaining = word[:i] + word[i+1:]
            find_anagrams(remaining, anagrams)
            # Sort the characters and add to the list of anagrams
            anagrams.append(''.join(sorted(word)))
    return anagrams

def main():
    """
    Main function to test the Anagram Finder.
    
    :return: None
    """
    word = 'listen'
    print(f"Anagrams of '{word}' are:")
    for anagram in find_anagrams(word):
        print(anagram)

if __name__ == '__main__':
    main()