# Guessing Game

# Import necessary libraries
import random

# Set the secret number
secret_number = random.randint(1, 100)

# Initialize attempts counter
attempts = 0

# Define a function to check if the guess is correct
def check_guess(guess):
    global attempts
    if guess < secret_number:
        print("Too low!")
    elif guess > secret_number:
        print("Too high!")
    else:
        print(f"Congratulations! You guessed it in {attempts} attempts.")
        return True
    attempts += 1
    return False

# Main game loop
while True:
    # Ask the user for a number
    user_guess = int(input("Guess a number between 1 and 100: "))
    
    # Check if the guess is correct
    if check_guess(user_guess):
        break

if __name__ == '__main__':
    main()