# Guessing Game

import random

def main():
    # Generate a random number between 1 and 100
    number_to_guess = random.randint(1, 100)
    
    # Initialize the number of attempts to 0
    attempts = 0
    
    print("Welcome to the Guessing Game!")
    print("Try to guess a number between 1 and 100.")
    
    while True:
        # Ask the user for their guess
        guess = int(input("Enter your guess: "))
        
        # Check if the guess is correct
        if guess == number_to_guess:
            print(f" Congratulations! You guessed correctly in {attempts} attempts.")
            break
        
        # If the guess is too high, give a hint
        elif guess > number_to_guess:
            print("Too high! Try again.")
        
        # If the guess is too low, give a hint
        else:
            print("Too low! Try again.")
        
        # Increment the number of attempts
        attempts += 1

if __name__ == '__main__':
    main()