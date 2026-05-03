# Word Frequency Counter
import re
from collections import defaultdict

def count_word_frequencies(text):
    # Remove punctuation, convert to lowercase, and split into words
    words = re.sub(r'[^\w\s]', '', text).lower().split()
    
    # Initialize dictionary to store word frequencies
    frequency_dict = defaultdict(int)
    
    # Count the frequency of each word
    for word in set(words):
        frequency_dict[word] += words.count(word)
    
    return dict(frequency_dict)

def main():
    if __name__ == '__main__':
        text = "This is a test. This is only a test. Testing, testing."
        print("Word Frequencies:")
        print(count_word_frequencies(text))

if __name__ == '__main__':
    main()