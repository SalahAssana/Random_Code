# Guess My Number

import random

def main():
    # Generate a random number between 1 and 100
    my_number = random.randint(1, 100)

    print("Welcome to 'Guess My Number'!")
    print("I'm thinking of a number between 1 and 100.")

    while True:
        # Ask the user for their guess
        user_guess = int(input("What's your guess? "))

        if user_guess < my_number:
            print("Too low! Try again.")
        elif user_guess > my_number:
            print("Too high! Try again.")
        else:
            print(f"Congratulations, you guessed it! The number was {my_number}.")
            break

if __name__ == '__main__':
    main()