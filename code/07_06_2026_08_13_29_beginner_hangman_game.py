# Hangman Game - A simple text-based game where the user tries to guess a word by inputting individual letters.

import random

# List of words for the game
words = ['apple', 'banana', 'cherry', 'date', 'elderberry']

# Choose a random word from the list
word_to_guess = random.choice(words)

# Create a list to store the guessed letters
guessed_letters = ['_'] * len(word_to_guess)

# Set the number of lives the player has
lives = 6

print('Welcome to Hangman! You have', lives, 'lives.')

while True:
    # Print the current state of the word
    print(' '.join(guessed_letters))

    # Ask the user for a letter to guess
    guess = input('Guess a letter: ').lower()

    if len(guess) != 1:
        print('Please enter a single letter.')
        continue

    if guess in guessed_letters:
        print('You already guessed that letter! Try again.')
        continue

    # Check if the guessed letter is in the word
    if guess in word_to_guess:
        # Reveal the guessed letter in the word
        for i, letter in enumerate(word_to_guess):
            if letter == guess:
                guessed_letters[i] = guess
    else:
        # The guessed letter is not in the word, so reduce the number of lives
        print('That letter is not in the word. You lose a life.')
        lives -= 1

    # Check if the user has won or run out of lives
    if '_' not in guessed_letters:
        print('Congratulations! You guessed the word:', word_to_guess)
        break
    elif lives == 0:
        print('Game over. The word was:', word_to_guess)
        break

if __name__ == '__main__':
    pass