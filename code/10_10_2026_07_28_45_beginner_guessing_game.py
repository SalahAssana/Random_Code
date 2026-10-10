# Guessing Game
import random

if __name__ == '__main__':
    # Set the range of numbers (inclusive)
    lower = 1
    upper = 100
    
    # Generate a random number within the range
    target_number = random.randint(lower, upper)
    
    print(f"Welcome to the Guessing Game! I'm thinking of a number between {lower} and {upper}.")
    
    while True:
        # Ask for user input
        guess = int(input("What's your guess? "))
        
        if guess < target_number:
            print("Too low, try again!")
        elif guess > target_number:
            print("Too high, try again!")
        else:
            print(f"Congratulations! You guessed the number: {target_number}")
            break