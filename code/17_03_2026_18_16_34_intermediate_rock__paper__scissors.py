import random

def get_computer_move():
    """Get computer's move randomly"""
    moves = ['rock', 'paper', 'scissors']
    return random.choice(moves)

def determine_winner(player_move, computer_move):
    """Determine the winner of the game"""
    if player_move == computer_move:
        return "It's a tie!"
    elif (player_move == 'rock' and computer_move == 'scissors') or \
         (player_move == 'paper' and computer_move == 'rock') or \
         (player_move == 'scissors' and computer_move == 'paper'):
        return "You win!"
    else:
        return "Computer wins!"

def play_game():
    """Play a game of rock, paper, scissors"""
    player_moves = ['rock', 'paper', 'scissors']
    while True:
        player_move = input("Enter your move (rock/paper/scissors) or 'q' to quit: ").lower()
        if player_move == 'q':
            break
        if player_move not in player_moves:
            print("Invalid move. Please try again.")
            continue
        computer_move = get_computer_move()
        print(f"Computer's move: {computer_move}")
        result = determine_winner(player_move, computer_move)
        print(result)

if __name__ == '__main__':
    play_game()