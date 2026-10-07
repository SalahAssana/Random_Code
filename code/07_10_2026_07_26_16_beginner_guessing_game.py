import random

# Initialize a secret number
secret_number = random.randint(1, 100)

while True:
    # Ask the user to guess the number
    user_guess = int(input("Guess a number between 1 and 100: "))

    # Check if the user guessed correctly
    if user_guess == secret_number:
        print("Congratulations! You guessed the correct number.")
        break
    elif user_guess < secret_number:
        print("Too low, try again!")
    else:
        print("Too high, try again!")

if __name__ == '__main__':
    pass