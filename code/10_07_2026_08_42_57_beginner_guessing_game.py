# Guessing Game

import random

if __name__ == '__main__':
    # Set the secret number
    secret_number = random.randint(1, 100)
    
    # Initialize the number of attempts
    attempts = 0
    
    print("Welcome to the guessing game!")
    print("I'm thinking of a number between 1 and 100.")
    print("Try to guess it.")
    
    while True:
        # Get the user's guess
        guess = int(input("Enter your guess: "))
        
        # Check if the guess is correct
        if guess == secret_number:
            print(f"Congratulations! You found the number in {attempts} attempts.")
            break
        
        # If the guess is too high or low, give a hint
        elif guess > secret_number:
            print("Too high. Try again!")
        else:
            print("Too low. Try again!")
        
        # Increment the number of attempts