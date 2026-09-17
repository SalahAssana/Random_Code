# Guessing Game - A simple game where the user tries to guess a randomly generated number.

import random
import time

# Set the secret number
secret_number = random.randint(1, 100)

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask the user for their guess
    guess = int(input("Enter your guess: "))

    # Check if the guess is correct
    if guess == secret_number:
        print(f" Congratulations! You guessed it in {guess} attempts.")
        break

    # If not, tell them if they're too high or too low
    elif guess < secret_number:
        print("Your guess was too low. Try again!")
    else:
        print("Your guess was too high. Try again!")

    # Wait 1 second before asking for the next guess
    time.sleep(1)