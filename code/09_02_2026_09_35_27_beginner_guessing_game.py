# Guessing Game
import random

if __name__ == '__main__':
    # Set the range for the guessing game (1-100)
    number_to_guess = random.randint(1, 100)

    print("Welcome to the Guessing Game!")
    print("I'm thinking of a number between 1 and 100.")

    while True:
        try:
            # Ask the user for their guess
            guess = int(input("Take a guess: "))

            if guess < 1 or guess > 100:
                print("Invalid input! Please enter a number between 1 and 100.")
            elif guess == number_to_guess:
                print(f"Congratulations, you guessed it! The number was {number_to_guess}.")
                break
            else:
                # Provide hints for high/low guesses
                if guess < number_to_guess:
                    print("Too low! Try guessing again.")
                else:
                    print("Too high! Try guessing again.")

        except ValueError:
            print("Invalid input! Please enter a whole number.")