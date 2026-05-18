import random

# Generate a random number for the game
target_number = random.randint(1, 100)

while True:
    # Ask the user to guess the number
    user_guess = int(input("Guess the number (1-100): "))

    # Check if the user's guess is correct
    if user_guess == target_number:
        print(" Congratulations! You guessed correctly!")
        break
    elif user_guess < target_number:
        print("Too low, try again!")
    else:
        print("Too high, try again!")

if __name__ == '__main__':
    pass