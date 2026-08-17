# Simple Rock Paper Scissors Game

import random

# List of possible choices
choices = ["rock", "paper", "scissors"]

def get_computer_choice():
    # Generate a random choice for the computer
    return random.choice(choices)

def get_user_choice():
    # Ask the user for their choice
    while True:
        user_choice = input("Enter your choice (rock, paper, or scissors): ")
        if user_choice.lower() in choices:
            return user_choice.lower()
        else:
            print("Invalid choice. Try again.")

def determine_winner(user_choice, computer_choice):
    # Determine the winner based on the game rules
    if user_choice == computer_choice:
        return "Tie!"
    elif (user_choice == "rock" and computer_choice == "scissors") or \
         (user_choice == "paper" and computer_choice == "rock") or \
         (user_choice == "scissors" and computer_choice == "paper"):
        return "You win!"
    else:
        return "Computer wins!"

if __name__ == '__main__':
    # Start the game
    print("Let's play Rock Paper Scissors!")
    
    computer_choice = get_computer_choice()
    user_choice = get_user_choice()
    
    print(f"Computer chose: {computer_choice}")
    print(f"You chose: {user_choice}")
    
    winner = determine_winner(user_choice, computer_choice)
    print(winner)