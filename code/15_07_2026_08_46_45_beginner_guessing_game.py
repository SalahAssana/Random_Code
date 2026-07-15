# Guessing Game
import random

# Set the winning number
winning_number = random.randint(1, 100)

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")
print("Try to guess it!")

while True:
    # Ask the user for their guess
    user_guess = int(input("Guess a number: "))

    # Check if the user guessed correctly
    if user_guess == winning_number:
        print(f" Congratulations! You guessed the number: {winning_number}!")
        break
    elif user_guess > winning_number:
        print("Too high, try again!")
    else:
        print("Too low, try again!")

if __name__ == '__main__':
    # Run the game if this script is run directly
    GuessingGame()