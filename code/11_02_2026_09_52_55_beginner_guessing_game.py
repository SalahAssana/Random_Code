# Guessing Game
import random

def main():
    # Set the target number
    target = random.randint(1, 100)
    
    # Initialize attempts and guess
    attempts = 0
    guess = None
    
    print("Guess a number between 1-100!")
    
    while True:
        user_input = input("Enter your guess: ")
        
        try:
            guess = int(user_input)
        except ValueError:
            print("Invalid input. Please enter a number.")
            continue
        
        attempts += 1
        
        if guess < target:
            print("Too low! Try again.")
        elif guess > target:
            print("Too high! Try again.")
        else:
            print(f"Congratulations, you guessed the number in {attempts} attempts!")
            break

if __name__ == '__main__':
    main()