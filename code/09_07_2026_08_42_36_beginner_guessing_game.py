import random

# Set the range for the randomly generated number
min_value = 1
max_value = 100

# Generate a random number within the set range
random_number = random.randint(min_value, max_value)

print("Welcome to the Guessing Game!")
print(f"I'm thinking of a number between {min_value} and {max_value}.")
print("Try to guess it!")

while True:
    # Get the user's guess
    user_guess = int(input("Enter your guess: "))

    if user_guess < min_value or user_guess > max_value:
        print(f"Sorry, {user_guess} is out of range. Try again!")
    elif user_guess == random_number:
        print(f"Congratulations! You guessed it correctly. The number was indeed {random_number}.")
        break
    else:
        if user_guess < random_number:
            print("Your guess is too low. Try a higher number.")
        else:
            print("Your guess is too high. Try a lower number.")