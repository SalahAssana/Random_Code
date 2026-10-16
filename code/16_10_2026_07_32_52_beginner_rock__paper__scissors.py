# Rock, Paper, Scissors Game

import random

choices = ["rock", "paper", "scissors"]

def get_computer_choice():
    return random.choice(choices)

def determine_winner(player_choice, computer_choice):
    if player_choice == computer_choice:
        return "Tie!"
    elif (player_choice == "rock" and computer_choice == "scissors") or \
         (player_choice == "paper" and computer_choice == "rock") or \
         (player_choice == "scissors" and computer_choice == "paper"):
        return "Player wins!"
    else:
        return "Computer wins!"

def play_game():
    player_score = 0
    computer_score = 0

    for _ in range(3):
        player_choice = input("Enter your choice (rock, paper, scissors): ")
        while player_choice not in choices:
            player_choice = input("Invalid choice. Enter your choice again: ")

        computer_choice = get_computer_choice()
        print(f"Computer chose {computer_choice}.")

        winner = determine_winner(player_choice, computer_choice)
        print(winner)

        if winner == "Player wins!":
            player_score += 1
        elif winner == "Computer wins!":
            computer_score += 1

    print(f"Final score: Player - {player_score}, Computer - {computer_score}")

if __name__ == '__main__':
    play_game()