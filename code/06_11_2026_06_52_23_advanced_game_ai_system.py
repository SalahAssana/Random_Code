import random
from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score
from collections import deque
import numpy as np

class Game:
    def __init__(self):
        self.player_moves = deque(maxlen=100)
        self.computer_moves = deque(maxlen=100)

    def generate_move(self, player_history, computer_history):
        # Use neural network to predict next move based on history
        X_player = StandardScaler().fit_transform(np.array(player_history).reshape(-1, 1))
        X_computer = StandardScaler().fit_transform(np.array(computer_history).reshape(-1, 1))
        predicted_move = self.nn.predict((X_player[-1], X_computer[-1]))

        # Use Q-learning to update computer's strategy based on player's moves
        self.q_learning(player_history, computer_history)

        return predicted_move

    def q_learning(self, player_history, computer_history):
        for i in range(len(player_history)):
            state = (player_history[i], computer_history[i])
            action = random.choice([0, 1])  # Choose a random move
            reward = self.get_reward(action)
            next_state = (player_history[i+1], computer_history[i+1])

            if len(self.player_moves) > i:
                self.q_learning.update(state, action, reward, next_state)

    def get_reward(self, action):
        if action == 0 and random.random() < 0.5:
            return 1
        elif action == 1 and random.random() < 0.3:
            return -1
        else:
            return 0

class QLearning:
    def __init__(self):
        self.q_table = {}

    def update(self, state, action, reward, next_state):
        if state not in self.q_table:
            self.q_table[state] = {}
        self.q_table[state][action] += reward
        for key in list(self.q_table[state].keys()):
            if key not in next_state and self.q_table[state][key] < 0.5:
                del self.q_table[state][key]

    def get_action(self, state):
        max_value = -1
        best_action = None
        for action, value in self.q_table.get(state, {}).items():
            if value > max_value:
                max_value = value
                best_action = action

        return random.choice([0, 1]) if best_action is None else best_action

nn = MLPClassifier(hidden_layer_sizes=(10,))
q_learning = QLearning()

if __name__ == '__main__':
    game = Game()
    for _ in range(10000):
        player_move = random.randint(0, 1)
        computer_move = game.generate_move(game.player_moves, game.computer_moves)
        game.player_moves.append(player_move)
        game.computer_moves.append(computer_move)

    while True:
        player_move = input("Enter your move (0 or 1): ")
        computer_move = game.generate_move(game.player_moves, game.computer_moves)
        if computer_move == int(player_move):
            print("Computer wins!")
        else:
            print("You win!")