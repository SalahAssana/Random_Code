# Guessing Game
import random

# Set the secret number
secret_number = random.randint(1, 100)

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")
print("Try to guess it!")

while True:
    # Ask the user for their guess
    user_guess = int(input("Enter your guess: "))

    # Check if the guess is correct
    if user_guess == secret_number:
        print(f" Congratulations! You guessed correctly. The number was {secret_number}.")
        break
    elif user_guess < secret_number:
        print("Too low! Try again.")
    else:
        print("Too high! Try again.")

if __name__ == '__main__':
    pass