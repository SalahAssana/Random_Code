# Guessing Game
import random

def game():
    # Start by choosing a random number between 1 and 100
    number_to_guess = random.randint(1, 100)
    
    # Initialize attempts to 0
    attempts = 0
    
    print("Welcome to the guessing game!")
    print("I'm thinking of a number between 1 and 100.")
    
    while True:
        # Ask the user for their guess
        user_guess = int(input("Guess a number: "))
        
        # Check if the user's guess is correct
        if user_guess == number_to_guess:
            print(f"Congratulations! You found the number in {attempts} attempts.")
            break
        
        # If the user's guess is not correct, provide a hint
        elif user_guess < number_to_guess:
            print("Too low! Try again.")
        else:
            print("Too high! Try again.")
        
        # Increment the attempt counter
        attempts += 1

if __name__ == '__main__':
    game()