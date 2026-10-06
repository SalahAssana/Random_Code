# Guessing Game
import random

# Set the secret number
secret_number = random.randint(1, 100)

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask the user for their guess
    user_guess = int(input("What's your guess? "))

    # Check if the user guessed correctly
    if user_guess == secret_number:
        print(f" Congratulations! You guessed it. The secret number was {secret_number}.")
        break

    # If not, give a hint
    elif user_guess < secret_number:
        print("Too low! Try again.")
    else:
        print("Too high! Try again.")

if __name__ == '__main__':
    guess_game()