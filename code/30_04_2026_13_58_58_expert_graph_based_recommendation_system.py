# graph_recommendation_system.py

import networkx as nx
import numpy as np
from scipy.spatial.distance import cosine
from sklearn.metrics.pairwise import linear_kernel
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.preprocessing import Normalizer

class UserItemGraph:
    def __init__(self):
        self.graph = nx.Graph()

    def add_user_item(self, user_id, item_id, rating):
        self.graph.add_node(user_id)
        self.graph.add_node(item_id)
        self.graph.add_edge(user_id, item_id, weight=rating)

    def get_similarity(self, user_id1, user_id2):
        user1_items = [item for _, item in self.graph.neighbors(user_id1)]
        user2_items = [item for _, item in self.graph.neighbors(user_id2)]

        common_items = set(user1_items) & set(user2_items)
        if not common_items:
            return 0

        user1_vector = np.array([self.graph[user_id1][item]['weight'] for item in common_items])
        user2_vector = np.array([self.graph[user_id2][item]['weight'] for item in common_items])

        cosine_similarity = cosine(user1_vector, user2_vector)
        return 1 - cosine_similarity

    def get_recommendations(self, user_id):
        similar_users = {}
        for other_user_id in self.graph.nodes:
            if other_user_id != user_id:
                similarity = self.get_similarity(user_id, other_user_id)
                if similarity > 0.5:
                    similar_users[other_user_id] = similarity

        sorted_similar_users = sorted(similar_users.items(), key=lambda x: x[1], reverse=True)

        recommended_items = set()
        for similar_user_id, _ in sorted_similar_users[:3]:
            for item_id in self.graph.neighbors(similar_user_id):
                if item_id not in self.graph.neighbors(user_id) and item_id not in recommended_items:
                    recommended_items.add(item_id)

        return list(recommended_items)

if __name__ == '__main__':
    graph = UserItemGraph()
    graph.add_user_item('user1', 'item1', 4)
    graph.add_user_item('user1', 'item2', 3)
    graph.add_user_item('user1', 'item3', 5)
    graph.add_user_item('user2', 'item1', 5)
    graph.add_user_item('user2', 'item4', 4)
    graph.add_user_item('user3', 'item2', 3)
    graph.add_user_item('user3', 'item5', 5)

    recommended_items = graph.get_recommendations('user1')