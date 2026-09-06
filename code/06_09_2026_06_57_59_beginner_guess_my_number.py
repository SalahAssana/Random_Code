# Guess My Number
import random

def game():
    # Generate a random number between 1 and 100
    secret_number = random.randint(1, 100)
    
    # Initialize the number of attempts
    attempts = 0
    
    while True:
        # Ask the user to guess the number
        guess = int(input("Guess my number (between 1 and 100): "))
        
        # Check if the user's guess is correct
        if guess == secret_number:
            print(f"Congratulations! You guessed it in {attempts} attempts.")
            break
        
        # If not, ask again
        elif guess < secret_number:
            print("Too low. Try again!")
        else:
            print("Too high. Try again!")
        
        # Increment the number of attempts
        attempts += 1

if __name__ == '__main__':
    game()