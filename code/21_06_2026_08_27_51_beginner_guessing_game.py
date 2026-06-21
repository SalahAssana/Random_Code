import random
import time

def guessing_game():
    print("Welcome to the Guessing Game!")
    print("You will be asked to guess a number.")
    print("If you guess correctly, you win! If not, I'll keep generating new numbers until you get it right.")

    # Generate a random number between 1 and 100
    target_number = random.randint(1, 100)
    attempts = 0

    while True:
        user_guess = int(input("Enter your guess: "))
        attempts += 1

        if user_guess == target_number:
            print(f" Congratulations! You guessed the number in {attempts} attempts.")
            break
        elif user_guess < target_number:
            print("Too low! Try again!")
        else:
            print("Too high! Try again!")

if __name__ == '__main__':
    guessing_game()