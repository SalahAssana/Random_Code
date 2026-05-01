# Project 3: Guessing Game
import random

def main():
    # Initialize the secret number
    secret_number = random.randint(1, 100)

    print("Welcome to the guessing game!")
    print("I'm thinking of a number between 1 and 100.")

    while True:
        # Get user's guess
        user_guess = int(input("What is your guess? "))

        if user_guess < secret_number:
            print("Too low! Try again.")
        elif user_guess > secret_number:
            print("Too high! Try again.")
        else:
            print(f" Congratulations! You guessed the number: {secret_number}")
            break

if __name__ == '__main__':
    main()