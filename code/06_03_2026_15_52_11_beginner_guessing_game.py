# Guessing Game

import random

number_to_guess = random.randint(1, 100)

while True:
    user_guess = int(input("Guess a number between 1 and 100: "))
    
    if user_guess < 1 or user_guess > 100:
        print("Invalid input. Please enter a number between 1 and 100.")
    elif user_guess == number_to_guess:
        print(f"Congratulations! You guessed the correct number {number_to_guess}.")
        break
    else:
        print("Try again!")