import random

# Set the secret number to be guessed
secret_number = random.randint(1, 100)

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask the user for their guess
    user_guess = int(input("What's your guess? "))

    if user_guess < secret_number:
        print("Too low! Try again.")
    elif user_guess > secret_number:
        print("Too high! Try again.")
    else:
        print(f"Congratulations, you guessed it! The number was {secret_number}.")
        break

if __name__ == '__main__':
    pass