# Guessing Game
import random

# Set the range of numbers to guess
min_num = 1
max_num = 100

if __name__ == '__main__':
    # Generate a random number within the set range
    target_number = random.randint(min_num, max_num)
    
    # Initialize the number of attempts
    attempts = 0
    
    print("Welcome to the Guessing Game!")
    print(f"I'm thinking of a number between {min_num} and {max_num}.")
    
    while True:
        # Ask the user for their guess
        user_guess = int(input("Guess the number: "))
        
        # Check if the user's guess is correct
        if user_guess == target_number:
            print(f"Congratulations! You guessed the number in {attempts} attempts.")
            break
        
        # If the guess is not correct, provide hints
        elif user_guess < target_number:
            print("Too low. Try again!")
        else:
            print("Too high. Try again!")
        
        # Increment the number of attempts