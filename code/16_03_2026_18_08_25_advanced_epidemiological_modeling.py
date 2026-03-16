import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt
import networkx as nx

class SIRModel:
    def __init__(self, N, beta, gamma):
        self.N = N
        self.beta = beta
        self.gamma = gamma

    def deriv(self, X, t):
        S, I, R = X
        dS_dt = -self.beta * S * I / self.N
        dI_dt = self.beta * S * I / self.N - self.gamma * I
        dR_dt = self.gamma * I
        return [dS_dt, dI_dt, dR_dt]

    def solve(self, t):
        X0 = [self.N-1, 1, 0]
        sol = odeint(self.deriv, X0, t)
        return sol

def draw_network(X, t):
    G = nx.Graph()
    for i in range(len(t)):
        if X[i][1] > 0.5:
            G.add_node(i, color='red')
        elif X[i][2] > 0.5:
            G.add_node(i, color='blue')
        else:
            G.add_node(i, color='green')

    pos = nx.spring_layout(G)
    nx.draw_networkx_nodes(G, pos, node_color=[node[1]['color'] for node in G.nodes(data=True)])
    nx.draw_networkx_edges(G, pos)
    plt.show()

if __name__ == '__main__':
    N = 1000
    beta = 0.0005
    gamma = 0.05

    t = np.linspace(0, 100)

    model = SIRModel(N, beta, gamma)
    X = model.solve(t)

    draw_network(X, t)