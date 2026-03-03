# Hangman Game in Python

import random

# List of words for the game
word_list = ["apple", "banana", "cherry", "date", "elderberry"]

def hangman():
    # Choose a random word from the list
    word = random.choice(word_list)
    
    # Initialize the guessed letters and the blank spaces
    guessed_letters = []
    blanks = "_" * len(word)
    
    while True:
        print(blanks)
        
        # Ask the user for their guess
        letter = input("Guess a letter: ").lower()
        
        if len(letter) != 1:
            print("Please enter a single letter.")
            continue
        
        if letter in guessed_letters:
            print("You already guessed this letter. Try again!")
            continue
        
        # Add the guessed letter to the list
        guessed_letters.append(letter)
        
        if letter not in word:
            print("Incorrect guess! The hangman gets another part...")
            # Update the blanks for incorrect guesses
            blanks = ""
            for i, letter_in_word in enumerate(word):
                if letter_in_word == "":
                    blanks += "_"
                elif letter_in_word.lower() != letter:
                    blanks += letter_in_word + "_"
                else:
                    blanks += letter_in_word
        else:
            print("Correct guess! The hangman is still alive...")
            # Update the blanks for correct guesses
            blanks = ""
            for i, letter_in_word in enumerate(word):
                if letter_in_word == "":
                    blanks += "_"
                elif letter_in_word.lower() != letter:
                    blanks += letter_in_word + "_"
                else:
                    blanks += letter_in_word
        
        # Check if the user has won
        if "_" not in blanks:
            print("Congratulations! You guessed the word!")
            break

if __name__ == '__main__':
    hangman()