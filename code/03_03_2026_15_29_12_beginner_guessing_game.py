# Guessing Game
# A simple game that asks for user input and checks if it's correct.

import random

# Set the number to be guessed
number_to_guess = random.randint(1, 100)

print("Welcome to the guessing game!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask the user for their guess
    user_guess = int(input("Guess a number: "))

    # Check if the user's guess is correct
    if user_guess == number_to_guess:
        print(" Congratulations! You guessed it correctly!")
        break
    elif user_guess < number_to_guess:
        print("Too low, try again!")
    else:
        print("Too high, try again!")

if __name__ == '__main__':
    guess_game()