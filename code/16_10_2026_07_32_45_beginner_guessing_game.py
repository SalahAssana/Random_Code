# Guessing Game

import random

# Predefined number to be guessed
number_to_guess = 42

# Initialize the number of guesses made
guesses_made = 0

if __name__ == '__main__':
    print("Welcome to the Guessing Game!")
    
    while True:
        # Ask the user for their guess
        user_guess = int(input("Guess a number between 1 and 100: "))
        
        # Check if the user's guess matches the predefined number
        if user_guess == number_to_guess:
            print(f"Congratulations! You guessed the correct number in {guesses_made} guesses.")
            break
        elif user_guess < number_to_guess:
            print("Your guess is too low. Try again!")
        else:
            print("Your guess is too high. Try again!")
        
        # Increment the number of guesses made
        guesses_made += 1