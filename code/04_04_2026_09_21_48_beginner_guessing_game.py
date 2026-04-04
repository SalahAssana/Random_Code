# Guessing Game
import random

def guess_game():
    # Initialize a random number between 1-100
    number_to_guess = random.randint(1, 100)
    
    # Set an initial range for the guessing
    low = 1
    high = 100
    
    while True:
        # Ask the user to input their guess
        user_guess = int(input("Guess a number between 1-100: "))
        
        # Check if the user's guess is too high or too low
        if user_guess < low or user_guess > high:
            print("Your guess is out of range. Try again!")
        elif user_guess == number_to_guess:
            print(f" Congratulations! You guessed the number {number_to_guess}.")
            break
        # If the user's guess is within the range, adjust the range for the next guess
        else:
            if user_guess < number_to_guess:
                low = user_guess + 1
            else:
                high = user_guess - 1

if __name__ == '__main__':
    guess_game()