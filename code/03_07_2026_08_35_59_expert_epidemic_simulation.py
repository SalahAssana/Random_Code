#!/usr/bin/env python3
# coding=utf8
from typing import List, Tuple
import numpy as np
import matplotlib.pyplot as plt
import networkx as nx

class Agent:
    def __init__(self, id: int):
        self.id = id
        self.state = 'S'  # Susceptible
        self.infected_since = None

    def infect(self) -> None:
        if self.state == 'S':
            self.state = 'I'  # Infectious
            self.infected_since = np.random.randint(1, 10)

    def recover(self) -> None:
        if self.state == 'I':
            self.state = 'R'  # Recovered

class EpidemicSimulation:
    def __init__(self, num_agents: int):
        self.num_agents = num_agents
        self.agents = [Agent(i) for i in range(num_agents)]
        self.graph = nx.Graph()

    def step(self) -> None:
        for agent in self.agents:
            if agent.state == 'I':
                # Infect neighboring agents
                neighbors = list(self.graph.neighbors(agent.id))
                for neighbor_id in neighbors:
                    neighbor_agent = next(agent for agent in self.agents if agent.id == neighbor_id)
                    neighbor_agent.infect()
        # Recover infectious agents
        for agent in self.agents:
            if agent.state == 'I' and np.random.rand() < 1 / (np.random.randint(1, 10) + 1):
                agent.recover()

    def visualize(self) -> None:
        nodes = {agent.id: agent.state for agent in self.agents}
        nx.draw_networkx(self.graph, pos=nx.spring_layout(self.graph), with_labels=True, node_color=['red' if state == 'I' else 'blue' if state == 'R' else 'green' for state in nodes.values()])
        plt.show()

    def run(self, steps: int) -> None:
        for _ in range(steps):
            self.step()
            print(f"Step {_+1}: {sum(1 for agent in self.agents if agent.state == 'I')} infectious agents")
        self.visualize()

if __name__ == '__main__':
    sim = EpidemicSimulation(1000)
    sim.run(50)