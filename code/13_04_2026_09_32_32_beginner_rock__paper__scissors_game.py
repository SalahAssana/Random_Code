# Rock, Paper, Scissors Game

import random

def get_computer_choice():
    choices = ['rock', 'paper', 'scissors']
    return random.choice(choices)

def get_user_choice():
    while True:
        user_choice = input("Enter your choice (rock/paper/scissors): ").lower()
        if user_choice in ['rock', 'paper', 'scissors']:
            return user_choice
        print("Invalid choice. Please enter rock, paper, or scissors.")

def determine_winner(user_choice, computer_choice):
    if user_choice == computer_choice:
        return "It's a tie!"
    if (user_choice == 'rock' and computer_choice == 'scissors') or \
       (user_choice == 'paper' and computer_choice == 'rock') or \
       (user_choice == 'scissors' and computer_choice == 'paper'):
        return "You win!"
    return "Computer wins!"

if __name__ == '__main__':
    print("Rock, Paper, Scissors Game")
    while True:
        user_choice = get_user_choice()
        computer_choice = get_computer_choice()
        print(f"Your choice: {user_choice}")
        print(f"Computer's choice: {computer_choice}")
        print(determine_winner(user_choice, computer_choice))
        play_again = input("Play again? (y/n): ").lower()
        if play_again != 'y':
            break