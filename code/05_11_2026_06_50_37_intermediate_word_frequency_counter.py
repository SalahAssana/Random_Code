# Word Frequency Counter
import re
from collections import defaultdict

class WordFrequencyCounter:
    def __init__(self):
        self.word_freq = defaultdict(int)

    def count_word_frequency(self, text):
        words = re.findall(r'\b\w+\b', text.lower())
        for word in set(words):  # remove duplicates
            self.word_freq[word] += words.count(word)

    def get_word_frequency(self):
        return dict(sorted(self.word_freq.items()))

def main():
    if __name__ == '__main__':
        counter = WordFrequencyCounter()
        text = "This is a test. This test is only a test."
        counter.count_word_frequency(text)
        for word, freq in counter.get_word_frequency().items():
            print(f"{word}: {freq}")

if __name__ == '__main__':
    main()