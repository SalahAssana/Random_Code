# Guessing Game for Beginners
import random

# Define the secret number
secret_number = random.randint(1, 100)

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Get user's guess
    user_guess = int(input("Guess my number: "))

    # Check if the guess is correct
    if user_guess == secret_number:
        print(f"Congratulations! You guessed my number: {secret_number}")
        break

    # Provide hints (high or low)
    elif user_guess < secret_number:
        print("Your guess is too low. Try again!")
    else:
        print("Your guess is too high. Try again!")

if __name__ == '__main__':
    pass