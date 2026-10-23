import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

class Agent:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
        self.velocity_x = 0
        self.velocity_y = 0
        self.velocity_z = 0

    def move(self):
        self.x += self.velocity_x
        self.y += self.velocity_y
        self.z += self.velocity_z

class Crowd:
    def __init__(self, size):
        self.size = size
        self.agents = [Agent(np.random.rand(), np.random.rand(), np.random.rand()) for _ in range(size)]

    def update(self):
        for agent in self.agents:
            if agent.x > 1 or agent.x < 0 or agent.y > 1 or agent.y < 0 or agent.z > 1 or agent.z < 0:
                agent.velocity_x = -agent.velocity_x
                agent.velocity_y = -agent.velocity_y
                agent.velocity_z = -agent.velocity_z

            if np.random.rand() < 0.01:
                agent.velocity_x = np.random.randn()
                agent.velocity_y = np.random.randn()
                agent.velocity_z = np.random.randn()

        for i in range(len(self.agents)):
            for j in range(i+1, len(self.agents)):
                distance = ((self.agents[i].x - self.agents[j].x)**2 + 
                            (self.agents[i].y - self.agents[j].y)**2 + 
                            (self.agents[i].z - self.agents[j].z)**2)**0.5
                if distance < 0.1:
                    agent1 = self.agents[i]
                    agent2 = self.agents[j]
                    angle = np.arctan2(agent2.y - agent1.y, agent2.x - agent1.x)
                    if angle > np.pi/4 and angle < 3*np.pi/4:
                        agent1.velocity_x += (agent2.x - agent1.x) / distance
                        agent1.velocity_y += (agent2.y - agent1.y) / distance

    def plot(self):
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        for agent in self.agents:
            ax.scatter(agent.x, agent.y, agent.z)
        plt.show()

if __name__ == '__main__':
    crowd = Crowd(1000)
    for _ in range(100):
        crowd.update()
    crowd.plot()