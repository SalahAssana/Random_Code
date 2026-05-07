import random

# Initialize the number of attempts to 0
attempts = 0

# Generate a random number between 1 and 100
number_to_guess = random.randint(1, 100)

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask the user for their guess
    user_guess = int(input("What's your guess? "))

    # Increment the number of attempts
    global attempts
    attempts += 1

    if user_guess < number_to_guess:
        print("Too low! Try again.")
    elif user_guess > number_to_guess:
        print("Too high! Try again.")
    else:
        print(f"Congratulations, you guessed it in {attempts} attempts!")
        break