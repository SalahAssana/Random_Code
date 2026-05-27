import random

# Define possible choices for Rock, Paper, Scissors game
choices = ['rock', 'paper', 'scissors']

def get_computer_choice():
    # Generate random choice for computer player
    return random.choice(choices)

def get_player_choice():
    # Ask user to input their choice
    while True:
        user_input = input("Enter your choice (rock/paper/scissors): ")
        if user_input.lower() in choices:
            return user_input.lower()
        else:
            print("Invalid choice. Please try again.")

def determine_winner(player_choice, computer_choice):
    # Determine the winner based on game rules
    if player_choice == computer_choice:
        return "It's a tie!"
    elif (player_choice == 'rock' and computer_choice == 'scissors') or \
         (player_choice == 'paper' and computer_choice == 'rock') or \
         (player_choice == 'scissors' and computer_choice == 'paper'):
        return "You win!"
    else:
        return "Computer wins!"

if __name__ == '__main__':
    # Main game loop
    while True:
        player_choice = get_player_choice()
        computer_choice = get_computer_choice()
        print(f"Computer chose: {computer_choice}")
        print(determine_winner(player_choice, computer_choice))
        play_again = input("Play again? (y/n): ")
        if play_again.lower() != 'y':
            break