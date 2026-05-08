# Guessing Game - A Simple Program for Beginners

import random

# Initialize variables to store the secret number and attempts made
secret_number = random.randint(1, 100)
attempts = 0

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask the user for their guess
    user_guess = int(input("What's your guess? "))

    # Check if the user guessed correctly
    attempts += 1
    if user_guess == secret_number:
        print(f" Congratulations! You found my number in {attempts} attempts.")
        break
    elif user_guess < secret_number:
        print("Too low! Try again.")
    else:
        print("Too high! Try again.")

if __name__ == '__main__':
    pass