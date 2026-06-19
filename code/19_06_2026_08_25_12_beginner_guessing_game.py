import random

# Define the range of numbers for the game
min_value = 1
max_value = 100

# Generate a random number within the defined range
secret_number = random.randint(min_value, max_value)

print("Welcome to the Guessing Game!")
print(f"I'm thinking of a number between {min_value} and {max_value}.")
print("Can you guess it?")

while True:
    # Ask the user for their guess
    user_guess = int(input("Enter your guess: "))

    # Check if the user's guess is correct
    if user_guess == secret_number:
        print(f" Congratulations! You guessed the number correctly.")
        break

    # Check if the user's guess is higher or lower than the secret number
    elif user_guess > secret_number:
        print("Your guess is too high. Try again!")
    else:
        print("Your guess is too low. Try again!")

if __name__ == '__main__':
    pass