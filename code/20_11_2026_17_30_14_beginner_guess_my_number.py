import random

# Set the range of numbers for the game
min_value = 1
max_value = 100

# Generate a random number to be guessed
secret_number = random.randint(min_value, max_value)

print("Welcome to Guess My Number!")
print(f"I'm thinking of a number between {min_value} and {max_value}.")
print("Try to guess it!")

while True:
    # Ask the user for their guess
    user_guess = int(input("Enter your guess: "))

    if user_guess < min_value or user_guess > max_value:
        print(f"Sorry, {user_guess} is out of range. Try again!")
    elif user_guess == secret_number:
        print(f"You got it! The number was indeed {secret_number}.")
        break
    else:
        if user_guess < secret_number:
            print("Too low! Guess higher.")
        else:
            print("Too high! Guess lower.")