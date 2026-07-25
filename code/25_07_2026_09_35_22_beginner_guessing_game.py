import random

# Set the winning number
winning_number = random.randint(1, 100)

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")

while True:
    # Ask the user for their guess
    user_guess = int(input("What's your guess? "))

    # Check if the user guessed correctly
    if user_guess == winning_number:
        print(f"Congratulations! You won! The number was {winning_number}.")
        break
    elif user_guess < winning_number:
        print("Too low! Try again.")
    else:
        print("Too high! Try again.")

if __name__ == '__main__':
    pass