import random

# Define possible moves
moves = ['rock', 'paper', 'scissors']

def get_computer_move():
    # Computer makes a random move
    return random.choice(moves)

def get_user_move():
    # Ask the user for their move
    while True:
        user_move = input("Enter your move (rock, paper, scissors): ")
        if user_move.lower() in moves:
            return user_move.lower()
        print("Invalid move. Try again!")

def determine_winner(user_move, computer_move):
    # Determine the winner based on game rules
    if user_move == computer_move:
        return "It's a tie!"
    if (user_move == 'rock' and computer_move == 'scissors') or \
       (user_move == 'paper' and computer_move == 'rock') or \
       (user_move == 'scissors' and computer_move == 'paper'):
        return "You win!"
    return "Computer wins!"

if __name__ == '__main__':
    while True:
        user_move = get_user_move()
        computer_move = get_computer_move()
        print(f"Computer chose: {computer_move}")
        print(f"You chose: {user_move}")
        print(determine_winner(user_move, computer_move))
        play_again = input("Play again? (yes/no): ")
        if play_again.lower() != 'yes':
            break