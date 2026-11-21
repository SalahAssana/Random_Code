import random

# Define difficulty levels
EASY = 10
MEDIUM = 50
HARD = 100

def play_game():
    # Choose difficulty level
    difficulty = input("Choose a difficulty level (easy/medium/hard): ")
    
    if difficulty.lower() == 'easy':
        target_number = random.randint(1, EASY)
    elif difficulty.lower() == 'medium':
        target_number = random.randint(1, MEDIUM)
    elif difficulty.lower() == 'hard':
        target_number = random.randint(1, HARD)
    else:
        print("Invalid choice. Defaulting to easy level.")
        target_number = random.randint(1, EASY)

    # Ask user for guess
    while True:
        try:
            guess = int(input(f"Guess the number (between 1 and {target_number}): "))
            
            if guess < 1 or guess > target_number:
                print("Invalid input. Try again!")
            else:
                break
        except ValueError:
            print("Invalid input. Please enter a number!")

    # Check if user guessed correctly
    if guess == target_number:
        print(f"Congratulations! You guessed the number: {target_number}")
    else:
        print(f"Sorry, you didn't get it right. The correct answer is: {target_number}")

if __name__ == '__main__':
    play_game()