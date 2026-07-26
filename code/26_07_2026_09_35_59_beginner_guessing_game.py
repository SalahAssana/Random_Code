# Guessing Game
import random

# Set the range of numbers for the game
min_num = 1
max_num = 100

# Generate a random number within the given range
target_number = random.randint(min_num, max_num)

print("Welcome to the Guessing Game!")
print(f"I'm thinking of a number between {min_num} and {max_num}.")
print("Try to guess it!")

while True:
    # Get user's guess
    user_guess = int(input("Enter your guess: "))

    # Check if the user guessed correctly
    if user_guess == target_number:
        print(f"Congratulations! You guessed the number ({target_number}) correctly!")
        break

    # If not, provide hints
    elif user_guess < target_number:
        print("Too low! The number is higher.")
    else:
        print("Too high! The number is lower.")

if __name__ == '__main__':
    pass