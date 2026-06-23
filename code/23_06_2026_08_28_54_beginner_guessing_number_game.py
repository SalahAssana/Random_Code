# Guessing Number Game
import random

def main():
    # Set the number to guess between 1 and 100
    number_to_guess = random.randint(1, 100)

    # Initialize the number of attempts
    attempts = 0

    print("Welcome to the Guessing Number Game!")
    print("I'm thinking of a number between 1 and 100.")
    print("Try to guess it in as few attempts as possible.")

    while True:
        # Ask the user for their guess
        user_guess = int(input("Enter your guess: "))

        # Check if the user guessed correctly
        if user_guess == number_to_guess:
            print(f" Congratulations! You guessed correctly in {attempts} attempts.")
            break

        # If not, give a hint (higher or lower)
        elif user_guess < number_to_guess:
            print("Too low! Try again.")
        else:
            print("Too high! Try again.")

        # Increment the number of attempts
        attempts += 1

if __name__ == '__main__':
    main()