# minimax.py

import math
import copy

class GameTreeSearcher:
    def __init__(self, game_state):
        self.game_state = game_state
        self.alpha = -math.inf
        self.beta = math.inf

    def evaluate(self, state):
        # This function evaluates the game state and returns a score.
        # The higher the score, the better for our player.
        pass

    def minimax(self, depth, is_maximizing_player):
        if depth == 0 or self.game_state.is_game_over():
            return self.evaluate(self.game_state)

        if is_maximizing_player:
            value = -math.inf
            for move in self.game_state.get_possible_moves():
                new_state = copy.deepcopy(self.game_state)
                new_state.apply_move(move)
                value = max(value, self.minimax(depth - 1, False))
                if value > self.beta:
                    return value
                self.beta = min(self.beta, value)
            return value

        else:
            value = math.inf
            for move in self.game_state.get_possible_moves():
                new_state = copy.deepcopy(self.game_state)
                new_state.apply_move(move)
                value = min(value, self.minimax(depth - 1, True))
                if value < self.alpha:
                    return value
                self.alpha = max(self.alpha, value)
            return value

    def get_best_move(self):
        best_value = -math.inf
        best_move = None
        for move in self.game_state.get_possible_moves():
            new_state = copy.deepcopy(self.game_state)
            new_state.apply_move(move)
            value = self.minimax(0, False)
            if value > best_value:
                best_value = value
                best_move = move
        return best_move

if __name__ == '__main__':
    # Example usage
    game_state = GameTreeSearcher(...)  # Initialize the game state
    searcher = GameTreeSearcher(game_state)
    best_move = searcher.get_best_move()
    print(f"The best move is {best_move}")