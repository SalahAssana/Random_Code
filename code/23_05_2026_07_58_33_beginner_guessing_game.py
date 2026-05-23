import random

# Set the range of numbers for the game
min_number = 1
max_number = 100

# Generate a random number within the range
secret_number = random.randint(min_number, max_number)

print("Welcome to the Guessing Game!")
print(f"I'm thinking of a number between {min_number} and {max_number}.")
print("Can you guess it?")

while True:
    # Ask the user for their guess
    user_guess = int(input("Enter your guess: "))

    # Check if the user's guess is correct
    if user_guess == secret_number:
        print(f" Congratulations! You guessed it correctly. The number was {secret_number}.")
        break
    # If the user's guess is too high, give a hint
    elif user_guess > secret_number:
        print("Oops, your guess is too high. Try again!")
    # If the user's guess is too low, give a hint
    else:
        print("Oops, your guess is too low. Try again!")

if __name__ == '__main__':
    pass