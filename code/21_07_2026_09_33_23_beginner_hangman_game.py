# Hangman Game in Python

import random

# List of words for the game
words = ["apple", "banana", "cherry", "date", "elderberry"]

# Choose a random word from the list
word_to_guess = random.choice(words)

# Create a list to store the guessed letters
guessed_letters = ["_"] * len(word_to_guess)

# Set for the number of lives (tries)
lives = 6

print("Welcome to Hangman!")
print("You have " + str(lives) + " lives.")

while True:
    # Print the current state of the word
    print(" ".join(guessed_letters))

    # Ask the user for a guess
    guess = input("Guess a letter: ").lower()

    # Check if the guess is in the word
    if guess in word_to_guess:
        # Reveal the correct letters
        for i in range(len(word_to_guess)):
            if word_to_guess[i] == guess:
                guessed_letters[i] = guess
    else:
        # Decrease the number of lives
        lives -= 1
        print("Incorrect! You have " + str(lives) + " lives left.")

    # Check if the user has won or lost
    if "_" not in guessed_letters:
        print("Congratulations, you won!")
        break
    elif lives == 0:
        print("Game over. The word was: " + word_to_guess)
        break

if __name__ == '__main__':