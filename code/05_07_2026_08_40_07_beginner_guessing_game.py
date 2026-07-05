# Guessing Game

import random

guess_number = 0

if __name__ == '__main__':
    target_number = random.randint(1, 100)
    
    while True:
        user_guess = int(input("Guess a number between 1 and 100: "))
        
        if user_guess < target_number:
            print("Too low. Try again!")
        elif user_guess > target_number:
            print("Too high. Try again!")
        else:
            print(f"Congratulations! You guessed {target_number} correctly.")
            break