# Rock Paper Scissors Game
# Written by [Your Name]

import random

def get_user_choice():
    while True:
        user_choice = input("Enter your choice (rock, paper, scissors): ")
        if user_choice.lower() in ["rock", "paper", "scissors"]:
            return user_choice.lower()
        print("Invalid choice. Please try again.")

def get_computer_choice():
    choices = ["rock", "paper", "scissors"]
    return random.choice(choices)

def determine_winner(user_choice, computer_choice):
    if user_choice == computer_choice:
        return "Tie"
    if (user_choice == "rock" and computer_choice == "scissors") or \
       (user_choice == "paper" and computer_choice == "rock") or \
       (user_choice == "scissors" and computer_choice == "paper"):
        return "User"
    return "Computer"

def main():
    user_score = 0
    computer_score = 0

    while True:
        user_choice = get_user_choice()
        computer_choice = get_computer_choice()

        print(f"User chose {user_choice}, Computer chose {computer_choice}.")

        winner = determine_winner(user_choice, computer_choice)

        if winner == "User":
            user_score += 1
            print("User wins this round!")
        elif winner == "Computer":
            computer_score += 1
            print("Computer wins this round!")
        else:
            print("It's a tie!")

        print(f"Score - User: {user_score}, Computer: {computer_score}\n")

        play_again = input("Play again? (yes/no): ")
        if play_again.lower() != "yes":
            break

    print(f"Final Score - User: {user_score}, Computer: {computer_score}")

if __name__ == '__main__':
    main()