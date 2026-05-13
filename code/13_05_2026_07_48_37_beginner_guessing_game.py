# Guessing Game
import random

def main():
    # Set the secret number
    secret_number = random.randint(1, 100)

    while True:
        # Ask for user's guess
        user_guess = int(input("Guess a number between 1 and 100: "))

        if user_guess == secret_number:
            print(" Congratulations! You guessed correctly.")
            break
        elif user_guess < secret_number:
            print("Try higher!")
        else:
            print("Try lower!")

if __name__ == '__main__':
    main()