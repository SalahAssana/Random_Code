# Word Frequency Counter
import re

class WordFrequencyCounter:
    def __init__(self):
        self.word_freq = {}

    def count_frequency(self, text):
        words = re.findall(r'\b\w+\b', text.lower())
        for word in set(words):
            if word not in self.word_freq:
                self.word_freq[word] = 0
            self.word_freq[word] += words.count(word)

    def display_results(self):
        print("Word Frequency Counter Results:")
        for word, freq in sorted(self.word_freq.items(), key=lambda x: x[1], reverse=True):
            print(f"{word}: {freq}")

if __name__ == '__main__':
    text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
    counter = WordFrequencyCounter()
    counter.count_frequency(text)
    counter.display_results()