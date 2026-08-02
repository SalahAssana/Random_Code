# Guessing Game

import random

def play_game():
    # Initialize game state variables
    number_to_guess = random.randint(1, 100)
    attempts = 0

    while True:
        # Get user's guess
        user_guess = int(input("Guess a number between 1 and 100: "))

        # Check if the user guessed correctly
        if user_guess == number_to_guess:
            print(f"Congratulations! You found the number in {attempts} attempts.")
            break

        # If not, update game state and ask for another guess
        elif user_guess < number_to_guess:
            print("Too low! Try again.")
        else:
            print("Too high! Try again.")

        attempts += 1

if __name__ == '__main__':
    play_game()