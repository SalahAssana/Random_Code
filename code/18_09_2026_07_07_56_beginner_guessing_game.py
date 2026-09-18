import random

# Set the range for the guessing game
min_value = 1
max_value = 100

# Generate a random number within the set range
secret_number = random.randint(min_value, max_value)

print("Welcome to the Guessing Game!")
print(f"I'm thinking of a number between {min_value} and {max_value}.")
print("Try to guess it!")

while True:
    # Ask the user for their guess
    user_guess = int(input("Enter your guess: "))

    # Check if the user's guess is correct
    if user_guess == secret_number:
        print(f"Congratulations! You guessed correctly. The number was {secret_number}.")
        break

    # If not, provide a hint
    elif user_guess < secret_number:
        print("Too low! Try again.")
    else:
        print("Too high! Try again.")

if __name__ == '__main__':
    pass