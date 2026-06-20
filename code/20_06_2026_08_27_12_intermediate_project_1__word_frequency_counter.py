# Project 1: Word Frequency Counter

import re
from collections import defaultdict

def count_word_frequency(file_name):
    """
    Counts the frequency of words in a given text file.

    Args:
        file_name (str): The name of the text file to process.

    Returns:
        dict: A dictionary with word frequencies.
    """
    try:
        # Open the file and read its content
        with open(file_name, 'r') as file:
            content = file.read()
    except FileNotFoundError:
        print(f"Error: File '{file_name}' not found.")
        return {}

    # Convert the text to lowercase and remove punctuation
    content = re.sub(r'[^\w\s]', '', content).lower()

    # Split the text into words
    words = content.split()

    # Initialize a dictionary to store word frequencies
    frequency = defaultdict(int)

    # Count the frequency of each word
    for word in words:
        frequency[word] += 1

    return dict(frequency)


if __name__ == '__main__':
    file_name = 'example.txt'  # Replace with your own file name
    print(count_word_frequency(file_name))