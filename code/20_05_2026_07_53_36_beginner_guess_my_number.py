# Guess My Number
import random

# Set the hidden number
hidden_number = random.randint(1, 100)

print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask the user for their guess
    user_guess = int(input("Guess the number: "))

    # Check if the guess is correct
    if user_guess == hidden_number:
        print(f"Congratulations! The hidden number was {hidden_number}.")
        break
    elif user_guess < hidden_number:
        print("Your guess is too low. Try again.")
    else:
        print("Your guess is too high. Try again.")

if __name__ == '__main__':
    pass