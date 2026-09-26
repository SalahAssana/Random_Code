import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt

class EpidemicSimulator:
    def __init__(self, N, beta, gamma):
        self.N = N
        self.beta = beta
        self.gamma = gamma
        self.S = N - 1
        self.I = 1
        self.R = 0

    def SIR_model(self, t, y):
        S, I, R = y
        dS_dt = -self.beta * S * I / self.N
        dI_dt = self.beta * S * I / self.N - self.gamma * I
        dR_dt = self.gamma * I
        return [dS_dt, dI_dt, dR_dt]

    def run_simulation(self, t):
        y0 = [self.S, self.I, self.R]
        solution = odeint(self.SIR_model, y0, t)
        S, I, R = solution.T
        plt.plot(t, S, 'b', label='Susceptible')
        plt.plot(t, I, 'r', label='Infected')
        plt.plot(t, R, 'g', label='Recovered')
        plt.xlabel('Time')
        plt.ylabel('Population')
        plt.title('Epidemic Simulation')
        plt.legend()
        plt.show()

    def monte_carlo_simulation(self, num_simulations):
        S_values = []
        I_values = []
        R_values = []
        for _ in range(num_simulations):
            S = self.N - 1
            I = 1
            R = 0
            t = np.arange(0, 100, 0.1)
            solution = odeint(self.SIR_model, [S, I, R], t)
            S_values.append(solution[-1][0])
            I_values.append(solution[-1][1])
            R_values.append(solution[-1][2])
        plt.hist(S_values, bins=50, alpha=0.5, label='Susceptible')
        plt.hist(I_values, bins=50, alpha=0.5, label='Infected')
        plt.hist(R_values, bins=50, alpha=0.5, label='Recovered')
        plt.xlabel('Population')
        plt.ylabel('Frequency')
        plt.title('Monte Carlo Simulation of Epidemic')
        plt.legend()
        plt.show()

if __name__ == '__main__':
    N = 10000
    beta = 0.0002
    gamma = 0.1
    simulator = EpidemicSimulator(N, beta, gamma)
    t = np.arange(0, 100, 0.1)
    simulator.run_simulation(t)
    simulator.monte_carlo_simulation(1000)