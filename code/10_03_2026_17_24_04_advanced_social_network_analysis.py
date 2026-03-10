import networkx as nx
import matplotlib.pyplot as plt
from collections import defaultdict

class SocialNetwork:
    def __init__(self):
        self.graph = nx.Graph()

    def add_user(self, user_id, platforms):
        if not self.graph.has_node(user_id):
            self.graph.add_node(user_id)
        for platform in platforms:
            self.add_connection(user_id, platform)

    def add_connection(self, user_id, platform):
        if not self.graph.has_edge(user_id, platform):
            self.graph.add_edge(user_id, platform)

    def get_connections(self, user_id):
        return list(self.graph.neighbors(user_id))

    def draw_graph(self):
        pos = nx.spring_layout(self.graph)
        nx.draw_networkx(self.graph, pos, with_labels=True)
        plt.show()

class Platform:
    def __init__(self, name):
        self.name = name
        self.users = set()

    def add_user(self, user_id):
        self.users.add(user_id)

    def get_users(self):
        return list(self.users)


if __name__ == '__main__':
    sn = SocialNetwork()
    
    # Add users and their connections
    user1 = Platform("Facebook")
    user2 = Platform("Instagram")
    user3 = Platform("Twitter")

    sn.add_user(1, ["Facebook", "Instagram"])
    sn.add_user(2, ["Instagram", "Twitter"])
    sn.add_user(3, ["Twitter", "Facebook"])

    # Add connections
    user1.add_user(1)
    user2.add_user(2)
    user3.add_user(3)

    # Draw the graph
    sn.draw_graph()