# Guessing Game
import random

if __name__ == '__main__':
    # Set the range for the number to guess
    min_number = 1
    max_number = 100
    
    # Generate a random number within the range
    target_number = random.randint(min_number, max_number)
    
    # Initialize the number of attempts
    attempts = 0
    
    while True:
        # Ask the user for their guess
        user_guess = int(input(f"Guess a number between {min_number} and {max_number}: "))
        
        # Check if the user's guess is correct
        if user_guess == target_number:
            print(f"Congratulations! You found the number in {attempts} attempts.")
            break
        
        # If the guess is incorrect, give a hint
        elif user_guess < target_number:
            print("Too low! Try again.")
        else:
            print("Too high! Try again.")
        
        # Increment the number of attempts
        attempts += 1