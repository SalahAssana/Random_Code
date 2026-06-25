# Guessing Game
import random

# Define the secret number
secret_number = random.randint(1, 100)

# Initialize the number of attempts
attempts = 0

print("Welcome to the guessing game!")
print("I'm thinking of a number between 1 and 100.")
print("Try to guess it.")

while True:
    # Ask the user for their guess
    user_guess = int(input("Enter your guess: "))

    # Check if the user's guess is correct
    if user_guess == secret_number:
        print(f" Congratulations! You found the number in {attempts} attempts.")
        break

    # If not, give a hint (higher or lower)
    elif user_guess < secret_number:
        print("Too low! Try again.")
    else:
        print("Too high! Try again.")

    # Increment the attempt counter
    attempts += 1

if __name__ == '__main__':
    pass