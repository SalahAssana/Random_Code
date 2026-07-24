import random

# Set a secret number between 1 and 100
secret_number = random.randint(1, 100)

print("Welcome to Guess My Number!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask the user for their guess
    user_guess = int(input("Guess my number: "))

    # Check if the user's guess is correct
    if user_guess == secret_number:
        print("Congratulations! You guessed my number!")
        break
    elif user_guess < secret_number:
        print("Too low! Guess again.")
    else:
        print("Too high! Guess again.")

if __name__ == '__main__':
    pass