import random

# Set the secret number to be guessed
secret_number = random.randint(1, 100)

while True:
    # Ask the user for their guess
    user_guess = int(input("Guess a number between 1 and 100: "))

    # Check if the user's guess is correct
    if user_guess == secret_number:
        print("Congratulations! You guessed the correct number.")
        break

    # If the user's guess is too high or too low, give them a hint
    elif user_guess > secret_number:
        print("Your guess is too high. Try again!")
    else:
        print("Your guess is too low. Try again!")

if __name__ == '__main__':
    pass