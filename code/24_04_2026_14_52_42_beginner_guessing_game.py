import random

# Set the range for the randomly generated number
min_value = 1
max_value = 100

print("Welcome to the Guessing Game!")
print(f"I'm thinking of a number between {min_value} and {max_value}.")
print("You have to guess it. Good luck!")

# Generate the random number
target_number = random.randint(min_value, max_value)

while True:
    # Ask the user for their guess
    user_guess = int(input("What's your guess? "))

    # Check if the guess is correct
    if user_guess == target_number:
        print(f"Congratulations! You guessed it: {target_number}.")
        break
    elif user_guess < target_number:
        print("Too low! Try again.")
    else:
        print("Too high! Try again.")

if __name__ == '__main__':
    pass