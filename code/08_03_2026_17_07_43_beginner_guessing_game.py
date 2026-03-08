import random

# Initialize a secret number between 1 and 100
secret_number = random.randint(1, 100)

while True:
    # Ask user for their guess
    try:
        guess = int(input("Guess a number between 1 and 100: "))
    except ValueError:
        print("Invalid input. Please enter a whole number.")
        continue

    # Check if the guess is correct
    if guess == secret_number:
        print(f"Congratulations! You guessed the number {secret_number} correctly!")
        break

    # Provide hints for incorrect guesses
    elif guess < secret_number:
        print("Too low. Try again!")
    else:
        print("Too high. Try again!")

if __name__ == '__main__':
    pass