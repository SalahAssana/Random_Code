# Project 3: Rock, Paper, Scissors Game

import random

# Define the choices for the game
choices = ["rock", "paper", "scissors"]

# Function to get user's choice
def get_user_choice():
    while True:
        user_choice = input("Enter your choice (rock/paper/scissors): ")
        if user_choice.lower() in [choice.lower() for choice in choices]:
            return user_choice
        print("Invalid choice. Please enter rock, paper, or scissors.")

# Function to generate computer's random choice
def get_computer_choice():
    return random.choice(choices)

# Main game function
def play_game():
    user_choice = get_user_choice()
    computer_choice = get_computer_choice()

    # Determine the winner
    if user_choice == computer_choice:
        print("It's a tie!")
    elif (user_choice == "rock" and computer_choice == "scissors") or \
         (user_choice == "paper" and computer_choice == "rock") or \
         (user_choice == "scissors" and computer_choice == "paper"):
        print(f"You won! {user_choice} beats {computer_choice}.")
    else:
        print(f"Computer won! {computer_choice} beats {user_choice}.")

if __name__ == '__main__':
    play_game()