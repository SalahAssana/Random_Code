import random

# Generate a random number between 1 and 100
secret_number = random.randint(1, 100)

while True:
    # Ask the user for their guess
    user_guess = int(input("Guess my number: "))

    if user_guess == secret_number:
        print(f"Congratulations! You guessed my number {secret_number}.")
        break
    elif user_guess < secret_number:
        print("Too low! Try again.")
    else:
        print("Too high! Try again.")

if __name__ == '__main__':
    pass