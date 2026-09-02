# Guessing Game
import random

def guess_game():
    # Generate a random number between 1 and 100
    target_number = random.randint(1, 100)
    
    # Initialize the number of attempts
    attempts = 0
    
    while True:
        # Ask the user to input their guess
        guess = int(input("Guess a number between 1 and 100: "))
        
        # Check if the guess is correct
        if guess == target_number:
            print(f"Congratulations! You guessed the number in {attempts} attempts.")
            break
        
        # If the guess is incorrect, ask again
        elif guess < target_number:
            print("Too low! Try again.")
        else:
            print("Too high! Try again.")
        
        # Increment the number of attempts
        attempts += 1

if __name__ == '__main__':
    guess_game()