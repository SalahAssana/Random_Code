# Guessing Game
import random

# Set the range for the generated number
min_num = 1
max_num = 100

# Generate a random number within the set range
target_number = random.randint(min_num, max_num)

print("Welcome to the Guessing Game!")
print(f"I'm thinking of a number between {min_num} and {max_num}.")
print("Try to guess it!")

while True:
    # Get user's guess
    user_guess = int(input("Enter your guess: "))

    # Check if the user guessed correctly
    if user_guess == target_number:
        print(f" Congratulations! You guessed it right! The number was {target_number}.")
        break
    elif user_guess < target_number:
        print("Your guess is too low. Try again!")
    else:
        print("Your guess is too high. Try again!")

if __name__ == '__main__':
    pass