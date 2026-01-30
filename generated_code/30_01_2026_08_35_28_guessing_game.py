# Guessing Game in Python

import random

def guessing_game():
    # Generate a random number between 1 and 100
    number_to_guess = random.randint(1, 100)
    
    # Initialize the number of attempts to 0
    attempts = 0
    
    while True:
        # Ask the user for their guess
        user_guess = int(input("Guess a number between 1 and 100: "))
        
        # Increment the number of attempts
        attempts += 1
        
        if user_guess < number_to_guess:
            print("Your guess is too low. Try again!")
        elif user_guess > number_to_guess:
            print("Your guess is too high. Try again!")
        else:
            print(f"Congratulations! You guessed the number in {attempts} attempts.")
            break

if __name__ == '__main__':
    guessing_game()