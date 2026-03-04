# Guess My Number
import random

secret_number = random.randint(1, 100)

while True:
    user_guess = int(input("Guess my number (between 1 and 100): "))

    if user_guess < secret_number:
        print("Your guess is too low. Try again!")
    elif user_guess > secret_number:
        print("Your guess is too high. Try again!")
    else:
        print(f" Congratulations! You guessed the number: {secret_number}")
        break

if __name__ == '__main__':
    pass