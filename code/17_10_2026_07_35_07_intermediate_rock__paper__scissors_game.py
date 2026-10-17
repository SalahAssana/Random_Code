# Rock, Paper, Scissors Game
import random

class Player:
    def __init__(self, name):
        self.name = name
        self.wins = 0
        self.losses = 0

    def get_move(self):
        moves = ["rock", "paper", "scissors"]
        return random.choice(moves)

def determine_winner(player1, player2):
    if player1.get_move() == player2.get_move():
        return None
    if (player1.get_move() == "rock" and player2.get_move() == "scissors") or \
       (player1.get_move() == "paper" and player2.get_move() == "rock") or \
       (player1.get_move() == "scissors" and player2.get_move() == "paper"):
        return player1.name
    return player2.name

def play_game(player1, player2):
    while True:
        move1 = player1.get_move()
        move2 = player2.get_move()
        winner = determine_winner(player1, player2)
        if winner is None:
            print(f"{player1.name} and {player2.name} have tied!")
        elif winner == player1.name:
            player1.wins += 1
            print(f"{player1.name} wins this round! Score: {player1.name} - {player1.wins}, {player2.name} - {player2.losses}")
        else:
            player2.losses += 1
            print(f"{player2.name} loses this round. Score: {player1.name} - {player1.wins}, {player2.name} - {player2.losses}")
        play_again = input("Do you want to play again? (yes/no): ")
        if play_again.lower() != "yes":
            break

if __name__ == '__main__':
    player1 = Player("Player 1")
    player2 = Player("Player 2")
    play_game(player1, player2)