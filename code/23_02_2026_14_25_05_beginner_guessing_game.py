# Guessing Game
import random

# Set a secret number
secret_number = random.randint(1, 100)

print("Welcome to the guessing game!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask user for their guess
    user_guess = int(input("What's your guess? "))

    if user_guess < secret_number:
        print("Too low! Try again.")
    elif user_guess > secret_number:
        print("Too high! Try again.")
    else:
        print(f"Congratulations! You guessed it: {secret_number}.")
        break

if __name__ == '__main__':
    pass