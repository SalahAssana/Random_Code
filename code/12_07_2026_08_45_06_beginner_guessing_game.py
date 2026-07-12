# Guessing Game
import random

def main():
    # Set the range for the generated number
    min_num = 1
    max_num = 100
    
    # Generate a random number within the specified range
    target_number = random.randint(min_num, max_num)
    
    # Initialize the number of attempts to 0
    attempt_count = 0
    
    print(f"Guess my number between {min_num} and {max_num}.")
    
    while True:
        # Ask for user's guess
        guess = int(input("Enter your guess: "))
        
        # Check if the guess is correct
        if guess == target_number:
            print(f"Congratulations! You guessed it in {attempt_count + 1} attempts.")
            break
        
        # If not, increment the attempt count and ask again
        else:
            attempt_count += 1
            print(f"Incorrect. Try again!")

if __name__ == '__main__':
    main()