import random

# Set the secret number
secret_number = random.randint(1, 100)

# Initialize attempts counter
attempts = 0

print("Welcome to Guess My Number!")
print("I'm thinking of a number between 1 and 100.")
print("Your goal is to guess it in as few attempts as possible.")

while True:
    # Ask the user for their guess
    user_guess = int(input("Enter your guess: "))

    # Increment attempts counter
    attempts += 1

    if user_guess < secret_number:
        print("Too low! Try again.")
    elif user_guess > secret_number:
        print("Too high! Try again.")
    else:
        print(f" Congratulations, you guessed it in {attempts} attempts!")
        break

if __name__ == '__main__':
    pass