import random

# Initialize the secret number
secret_number = random.randint(1, 100)

# Set the number of attempts allowed
attempts_allowed = 6

print("Welcome to 'Guess My Number'!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask the user for their guess
    user_guess = int(input("Enter your guess: "))

    # Check if the user's guess is correct
    if user_guess == secret_number:
        print(f"Congratulations! You guessed my number in {attempts_allowed} attempts.")
        break

    # Check if the user has run out of attempts
    elif attempts_allowed == 0:
        print("Sorry, you didn't guess my number. It was {}.".format(secret_number))
        break

    # Update the number of attempts left
    else:
        attempts_allowed -= 1
        print(f"Your guess is not correct. Try again! You have {attempts_allowed} attempts remaining.")