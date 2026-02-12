# Guessing Game - A simple number guessing game that introduces basic programming concepts such as variables and conditionals.

# Import necessary modules
import random

# Set the secret number
secret_number = random.randint(1, 100)

# Initialize the number of attempts made by the player
attempts_made = 0

if __name__ == '__main__':
    print("Welcome to the Guessing Game!")
    
    # Start the game loop
    while True:
        # Ask the player for their guess
        user_guess = int(input("Guess a number between 1 and 100: "))
        
        # Increment the attempts made counter
        attempts_made += 1
        
        # Check if the user's guess is correct
        if user_guess == secret_number:
            print(f"Congratulations! You guessed the number in {attempts_made} attempts.")
            break
        elif user_guess < secret_number:
            print("Too low! Try again.")
        else: