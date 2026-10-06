# Hangman Game
import random

# List of words to guess
words = ["apple", "banana", "cherry", "date", "elderberry"]

# Choose a random word from the list
word_to_guess = random.choice(words)

# Create a list to store guessed letters
guessed_letters = []

# Create a list to display the current state of the word
display_word = ["_"] * len(word_to_guess)

# Game loop
while True:
    # Print the current state of the word
    print(" ".join(display_word))
    
    # Ask the user for their guess
    guess = input("Guess a letter: ").lower()
    
    # Check if the guess is in the word
    if guess in word_to_guess:
        # Update the display word with the correct letters
        for i in range(len(word_to_guess)):
            if word_to_guess[i] == guess:
                display_word[i] = guess
    else:
        print("That letter is not in the word.")
    
    # Check if the user has guessed the entire word
    if "_" not in display_word:
        print("Congratulations, you've guessed the word!")
        break

if __name__ == '__main__':
    game()