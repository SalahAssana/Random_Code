# Word Frequency Counter
import re
from collections import defaultdict

def count_word_frequency(text):
    """
    Counts the frequency of each word in the given text.

    Args:
        text (str): The input text to process.

    Returns:
        dict: A dictionary where keys are words and values are their frequencies.
    """
    # Convert the text to lowercase and remove non-alphanumeric characters
    text = re.sub(r'[^a-zA-Z0-9\s]', '', text).lower()

    # Split the text into individual words
    words = text.split()

    # Initialize a dictionary to store word frequencies
    frequency_dict = defaultdict(int)

    for word in words:
        frequency_dict[word] += 1

    return dict(frequency_dict)


def main():
    """
    The main function that reads input from user and calls the count_word_frequency function.
    """
    if __name__ == '__main__':
        text = input("Enter a text: ")
        result = count_word_frequency(text)
        for word, frequency in result.items():
            print(f"{word}: {frequency}")


if __name__ == '__main__':
    main()