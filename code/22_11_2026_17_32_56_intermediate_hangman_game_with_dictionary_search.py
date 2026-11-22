# Hangman Game with Dictionary Search

import random

# Dictionary of words for the game
word_dict = {
    "apple": 7,
    "banana": 6,
    "cherry": 6,
    "date": 4,
    "elderberry": 9,
    "fig": 3,
    "grape": 5,
    "honeydew": 8
}

def generate_word(length):
    """
    Generates a random word of the given length.
    
    Args:
        length (int): The length of the word to be generated.

    Returns:
        str: A randomly selected word from the dictionary with the given length.
    """
    return [key for key in word_dict if len(key) == length][0]

def draw_hangman(attempts):
    """
    Draws the hangman's gallows based on the number of attempts made.
    
    Args:
        attempts (int): The number of attempts made by the player.

    Returns:
        str: A string representation of the hangman's gallows.
    """
    if attempts == 1:
        return " _ _ _ _ _"
    elif attempts == 2:
        return "| _ _ _ _ |"
    elif attempts == 3:
        return "| | _ _ _ | |"
    elif attempts == 4:
        return "| | | _ _ | | |"
    else:
        return "|_|_|_|_|_|_|"

def play_hangman():
    """
    Plays the hangman game.
    
    Returns:
        None
    """
    word = generate_word(random.randint(3, 9))
    attempts = 0
    guessed_word = ["_"] * len(word)
    while True:
        print("\n" + draw_hangman(attempts) + "\n")
        print(" ".join(guessed_word))
        guess = input("Guess a letter: ")
        if guess in word:
            guessed_word = [letter if letter == "_" else guess for (i, letter) in enumerate(word)]
        else:
            attempts += 1
        if "_" not in guessed_word:
            print("\nCongratulations! You guessed the word " + word + ".")
            return

if __name__ == '__main__':
    play_hangman()