import random

# Set the range for the random number
min_value = 1
max_value = 100

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between", min_value, "and", max_value)

# Generate a random number within the set range
target_number = random.randint(min_value, max_value)

guesses_left = 6

while guesses_left > 0:
    # Ask the user for their guess
    user_guess = int(input("Guess a number: "))

    if user_guess < target_number:
        print("Too low! Try again.")
    elif user_guess > target_number:
        print("Too high! Try again.")
    else:
        print("Congratulations, you won!")
        break

    # Decrement the number of guesses left
    guesses_left -= 1

    if guesses_left > 0:
        print("You have", guesses_left, "guesses left.")

if guesses_left == 0:
    print("Sorry, you ran out of guesses. The number was", target_number)