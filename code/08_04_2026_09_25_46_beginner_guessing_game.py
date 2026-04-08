# Guessing Game
import random

# Set the range for the game
MIN = 1
MAX = 100

def main():
    # Generate a random number within the range
    number_to_guess = random.randint(MIN, MAX)
    
    print("Welcome to the Guessing Game!")
    print(f"I'm thinking of a number between {MIN} and {MAX}.")
    
    while True:
        # Get user's guess
        user_guess = int(input("Guess a number: "))
        
        if user_guess < MIN or user_guess > MAX:
            print("Invalid input. Please try again.")
            continue
        
        # Check if the user guessed correctly
        if user_guess == number_to_guess:
            print(f"Congratulations! You guessed it: {number_to_guess}.")
            break
        elif user_guess < number_to_guess:
            print("Too low! Try again.")
        else:
            print("Too high! Try again.")

if __name__ == '__main__':
    main()