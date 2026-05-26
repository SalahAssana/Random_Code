# Guessing Game
import random

def guess_game():
    # Set the target number to be guessed
    target = random.randint(1, 100)
    
    # Initialize the number of attempts
    attempts = 0
    
    print("Welcome to the guessing game!")
    print("I'm thinking of a number between 1 and 100.")
    
    while True:
        # Ask the user for their guess
        user_guess = int(input("Guess a number: "))
        
        # Increment the number of attempts
        attempts += 1
        
        if user_guess < target:
            print("Too low! Try again.")
        elif user_guess > target:
            print("Too high! Try again.")
        else:
            print(f"Congratulations, you guessed it in {attempts} attempts!")
            break

if __name__ == '__main__':
    guess_game()