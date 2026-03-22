# Guess My Number - A Simple Guessing Game for Beginners

import random

# Set the target number to be guessed
target_number = random.randint(1, 100)

# Initialize the number of attempts made by the user
attempts = 0

print("Welcome to Guess My Number!")
print("I'm thinking of a number between 1 and 100.")
print("You can guess my number by typing a number from 1 to 100.")

while True:
    # Ask the user for their next guess
    user_guess = int(input("What's your next guess? "))

    # Check if the user guessed correctly
    if user_guess == target_number:
        print(f" Congratulations! You guessed my number in {attempts} attempts.")
        break

    # If not, increment the number of attempts and give a hint
    attempts += 1
    if user_guess < target_number:
        print("Your guess is too low. Try again!")
    else:
        print("Your guess is too high. Try again!")

if __name__ == '__main__':
    pass