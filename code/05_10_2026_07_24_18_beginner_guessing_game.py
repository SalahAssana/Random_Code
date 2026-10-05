# Guessing Game

import random

if __name__ == '__main__':
    # Set range for number to guess
    low = 1
    high = 100

    # Generate random number within range
    number_to_guess = random.randint(low, high)

    while True:
        try:
            # Ask user to guess a number
            user_guess = int(input("Guess a number between {} and {}: ".format(low, high)))
            
            if user_guess < low or user_guess > high:
                print("Invalid input. Please enter a number within the range.")
            elif user_guess == number_to_guess:
                print(" Congratulations! You guessed the correct number: {}".format(number_to_guess))
                break
            else:
                if user_guess < number_to_guess:
                    print("Your guess is too low. Try again!")
                else:
                    print("Your guess is too high. Try again!")
        except ValueError:
            print("Invalid input. Please enter an integer.")