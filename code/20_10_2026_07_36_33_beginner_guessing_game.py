import random

def guessing_game():
    print("Welcome to the Guessing Game!")
    low = 1
    high = 100
    guess = None
    
    while True:
        if guess is None:
            print(f"Think of a number between {low} and {high}.")
        else:
            if guess < (low + high) // 2:
                print("Too low! Try again.")
            elif guess > (low + high) // 2:
                print("Too high! Try again.")
            else:
                print(f"Congratulations! You guessed the number: {guess}.")
                break
        
        # Ask for user input
        guess = int(input(f"Enter your guess ({low} to {high}): "))

if __name__ == '__main__':
    guessing_game()