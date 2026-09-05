# Guessing Game - Beginner Level Implementation

import random

# Set the secret number to be guessed
secret_number = random.randint(1, 100)

# Initialize the number of attempts made by the user
attempts_made = 0

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask the user for their guess
    user_guess = int(input("What's your guess? "))

    # Increment the attempts made counter
    attempts_made += 1

    if user_guess == secret_number:
        print(f" Congratulations! You found the number in {attempts_made} attempts.")
        break
    elif user_guess < secret_number:
        print("Too low. Try again!")
    else:
        print("Too high. Try again!")

if __name__ == '__main__':
    pass