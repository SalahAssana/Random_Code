import numpy as np

class ErgodicMarkovChain:
    def __init__(self, num_states, transition_matrix):
        self.num_states = num_states
        self.transition_matrix = transition_matrix
        self.current_state = 0

    def step(self):
        current_state_probabilities = self.transition_matrix[self.current_state]
        cumulative_probabilities = np.cumsum(current_state_probabilities)
        random_number = np.random.rand()
        for i, prob in enumerate(cumulative_probabilities / cumulative_probabilities[-1]):
            if random_number < prob:
                self.current_state = i
                break

    def run_simulation(self, num_steps):
        for _ in range(num_steps):
            self.step()

if __name__ == '__main__':
    # Synthetic data: transition matrix representing a simple system with 3 states (A, B, C)
    # State A transitions to state B with probability 0.8 and to state C with probability 0.2
    # State B transitions to state A with probability 0.5 and to state C with probability 0.5
    # State C transitions to state A with probability 0.7 and to state B with probability 0.3
    transition_matrix = np.array([[0.8, 0.2], [0.5, 0.5], [0.7, 0.3]])

    ergodic_chain = ErgodicMarkovChain(3, transition_matrix)