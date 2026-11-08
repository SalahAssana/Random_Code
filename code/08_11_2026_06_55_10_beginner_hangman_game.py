# Hangman Game - Beginner Level Implementation
import random

# List of words for the game
words = ["apple", "banana", "cherry", "date", "elderberry"]

# Choose a random word from the list
word = random.choice(words)

# Create a list to store the guessed letters
guessed_letters = ["_"] * len(word)

# Set the number of chances the player has
chances = 10

print("Welcome to Hangman!")
print("You have", chances, "chances to guess the word.")

while True:
    print(" ".join(guessed_letters))
    
    # Ask the user for a letter to guess
    guess = input("Guess a letter: ").lower()
    
    if len(guess) != 1:
        print("Please enter a single letter.")
        continue
    
    if guess in guessed_letters:
        print("You already guessed that letter!")
        continue
    
    # Check if the guessed letter is in the word
    for i, letter in enumerate(word):
        if letter == guess:
            guessed_letters[i] = guess
    
    # If the player has guessed all the letters, they win!
    if "_" not in guessed_letters:
        print(" Congratulations! You won!")
        break
    
    # If the player runs out of chances, they lose
    if chances > 0:
        chances -= 1
        print("You have", chances, "chances left.")
    else:
        print("Sorry, you lost! The word was:", word)
        break

if __name__ == '__main__':
    hangman()