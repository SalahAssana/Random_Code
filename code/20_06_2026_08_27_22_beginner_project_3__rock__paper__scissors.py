import random

# Define possible choices for computer player and user
choices = ['rock', 'paper', 'scissors']

# Function to generate random choice for computer player
def get_computer_choice():
    return random.choice(choices)

# Function to determine the winner based on the game rules
def determine_winner(user_choice, computer_choice):
    if user_choice == computer_choice:
        return 'Tie'
    elif (user_choice == 'rock' and computer_choice == 'scissors') or \
         (user_choice == 'paper' and computer_choice == 'rock') or \
         (user_choice == 'scissors' and computer_choice == 'paper'):
        return 'User wins!'
    else:
        return 'Computer wins!'

# Main game loop
if __name__ == '__main__':
    user_choice = input("Enter your choice (rock, paper, scissors): ")
    
    while user_choice not in choices:
        print("Invalid choice. Please try again.")
        user_choice = input("Enter your choice (rock, paper, scissors): ")

    computer_choice = get_computer_choice()
    result = determine_winner(user_choice, computer_choice)
    print(f"Computer chose {computer_choice}. You {result}!")