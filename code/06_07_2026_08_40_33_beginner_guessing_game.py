# Guessing Game
import random

def guess_game():
    # Set a random number to be guessed
    target_number = random.randint(1, 100)
    
    # Initialize the number of attempts
    attempts = 0
    
    print("Welcome to the Guessing Game!")
    print("I'm thinking of a number between 1 and 100.")
    
    while True:
        # Ask the user for their guess
        guess = int(input("Guess a number: "))
        
        # Check if the guess is correct
        if guess == target_number:
            print(f"Congratulations! You guessed it in {attempts} attempts.")
            break
        
        # If not, increment the attempt counter and ask again
        else:
            attempts += 1
            print("Try again!")

if __name__ == '__main__':
    guess_game()