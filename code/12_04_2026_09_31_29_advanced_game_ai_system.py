import numpy as np
from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing import OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
import pandas as pd
from collections import defaultdict
from time import time

class GameAI:
    def __init__(self):
        self.player_data = []
        self.game_state_data = []

    def train_ai(self):
        # Preprocess data using ColumnTransformer and OneHotEncoder
        preprocessor = ColumnTransformer(transformers=[('ohe', OneHotEncoder(handle_unknown='ignore'))], remainder='mean'
                                          , categorize=['player_type', 'game_mode'])

        X_train, y_train = self.preprocess_data()
        ai_model = MLPClassifier(max_iter=10000)
        start_time = time()
        ai_model.fit(preprocessor.fit_transform(X_train), y_train)
        end_time = time()
        print(f"Training Time: {end_time - start_time} seconds")

    def preprocess_data(self):
        # Combine player and game state data
        combined_data = np.concatenate((np.array(self.player_data), np.array(self.game_state_data)), axis=0)

        # Convert labels to numerical values using OneHotEncoder
        ohe = OneHotEncoder(handle_unknown='ignore')
        one_hot_labels = ohe.fit_transform(np.array([['player1'], ['player2'], ...]))

        return combined_data, one_hot_labels

    def make_decision(self, game_state):
        X_test = [game_state]
        predicted_class = self.ai_model.predict(X_test)[0]

        if predicted_class == 'play':
            # Play the game
            print("Playing the game...")
        elif predicted_class == 'observe':
            # Observe the game
            print("Observing the game...")
        else:
            # Unknown decision
            print("Unknown decision...")

    def update_player_data(self, player_type):
        self.player_data.append([player_type])

    def update_game_state_data(self, game_mode):
        self.game_state_data.append([game_mode])

if __name__ == '__main__':
    ai = GameAI()

    # Initialize synthetic data
    for i in range(1000):
        ai.update_player_data('player1' if np.random.rand() < 0.5 else 'player2')
        game_modes = ['casual', 'competitive']
        ai.update_game_state_data(np.random.choice(game_modes))

    # Train AI model
    ai.train_ai()

    # Make a decision based on game state
    game_state = ['competitive']
    ai.make_decision(game_state)