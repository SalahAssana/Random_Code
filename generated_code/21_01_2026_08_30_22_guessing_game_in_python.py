# Guessing Game in Python

import random

def start_game():
    print("Welcome to the guessing game! I'm thinking of a number between 1 and 100.")
    print("Try to guess it!")

def get_guess():
    while True:
        try:
            guess = int(input("Enter your guess: "))
            if 1 <= guess <= 100:
                return guess
            else:
                print("Invalid input. Please enter a number between 1 and 100.")
        except ValueError:
            print("Invalid input. Please enter an integer.")

def check_guess(target, guess):
    if target == guess:
        print(f"Congratulations! You guessed the number: {target}")
    elif guess < target:
        print(f"Incorrect. The number is higher than your guess ({guess}). Try again!")
    else:
        print(f"Incorrect. The number is lower than your guess ({guess}). Try again!")

def main():
    if __name__ == '__main__':
        # Generate a random number between 1 and 100
        target = random.randint(1, 100)
        
        start_game()
        while True:
            guess = get_guess()
            check_guess(target, guess)

if __name__ == '__main__':
    main()