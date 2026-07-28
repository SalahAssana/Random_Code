# Guessing Game

import random

# Define the secret number
secret_number = random.randint(1, 100)

# Initialize the number of attempts
attempts = 0

print("Welcome to the Guessing Game!")
print("Guess a number between 1 and 100.")

while True:
    # Ask for user input
    guess = int(input("Enter your guess: "))

    # Increment the number of attempts
    attempts += 1

    if guess < secret_number:
        print("Your guess is too low. Try again!")
    elif guess > secret_number:
        print("Your guess is too high. Try again!")
    else:
        print(f" Congratulations! You found the correct answer in {attempts} attempts.")
        break

if __name__ == '__main__':
    pass