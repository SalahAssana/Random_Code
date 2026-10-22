import random

# Initialize the number to be guessed
number_to_guess = random.randint(1, 100)

# Initialize the number of attempts
attempts = 0

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")
print("You have to guess it in as few attempts as possible.")

while True:
    # Ask for user's guess
    user_guess = int(input("Enter your guess: "))

    # Increment the number of attempts
    attempts += 1

    if user_guess < number_to_guess:
        print("Your guess is too low. Try again!")
    elif user_guess > number_to_guess:
        print("Your guess is too high. Try again!")
    else:
        print(f" Congratulations! You guessed the number in {attempts} attempts.")
        break

if __name__ == '__main__':
    pass