import numpy as np
from scipy.spatial.distance import cosine
from sklearn.metrics.pairwise import euclidean_distances
from scipy.sparse import csr_matrix
from collections import defaultdict

class UserItemMatrix:
    def __init__(self):
        self.users = {}
        self.items = {}

    def add_user_item(self, user_id, item_id):
        if user_id not in self.users:
            self.users[user_id] = []
        self.users[user_id].append(item_id)
        
        if item_id not in self.items:
            self.items[item_id] = []
        self.items[item_id].append(user_id)

    def get_user_items(self, user_id):
        return self.users.get(user_id, [])

    def get_item_users(self, item_id):
        return self.items.get(item_id, [])


class CollaborativeFiltering:
    def __init__(self, user_item_matrix):
        self.user_item_matrix = user_item_matrix

    def calculate_similarity(self, user_id1, user_id2):
        user_items1 = set(self.user_item_matrix.get_user_items(user_id1))
        user_items2 = set(self.user_item_matrix.get_user_items(user_id2))

        intersection = user_items1.intersection(user_items2)
        union = user_items1.union(user_items2)

        return len(intersection) / len(union)


    def recommend_items(self, user_id, num_recommendations):
        similar_users = []
        for other_user in self.user_item_matrix.users:
            if other_user != user_id:
                similarity = self.calculate_similarity(user_id, other_user)
                similar_users.append((other_user, similarity))

        sorted_similar_users = sorted(similar_users, key=lambda x: x[1], reverse=True)

        recommended_items = []
        for similar_user in sorted_similar_users:
            common_items = set(self.user_item_matrix.get_user_items(user_id)) & set(self.user_item_matrix.get_item_users(similar_user[0]))
            for item in common_items:
                if item not in self.user_item_matrix.get_user_items(user_id):
                    recommended_items.append(item)

        return recommended_items[:num_recommendations]


class Evaluation:
    def __init__(self, user_item_matrix, collaborative_filtering):
        self.user_item_matrix = user_item_matrix
        self.collaborative_filtering = collaborative_filtering

    def calculate_precision(self, actual_items, predicted_items):
        true_positive_count = 0
        for item in predicted_items:
            if item in actual_items:
                true_positive_count += 1
        
        return true_positive_count / len(actual_items)


    def evaluate_recommendations(self, user_id, num_recommendations=10):
        actual_items = set(self.user_item_matrix.get_user_items(user_id))
        predicted_items = self.collaborative_filtering.recommend_items(user_id, num_recommendations)
        
        precision = self.calculate_precision(actual_items, predicted_items)

        return precision


if __name__ == '__main__':
    user_item_matrix = UserItemMatrix()
    
    # Add some sample data
    user_item_matrix.add_user_item(1, 1)
    user_item_matrix.add_user_item(1, 2)
    user_item_matrix.add_user_item(1, 3)
    user_item_matrix.add_user_item(2, 4)
    user_item_matrix.add_user_item(2, 5)
    user_item_matrix.add_user_item(3, 6)

    collaborative_filtering = CollaborativeFiltering(user_item_matrix)
    
    evaluation = Evaluation(user_item_matrix, collaborative_filtering)
    
    precision = evaluation.evaluate_recommendations(1)
    
    print(f"Precision for user 1: {precision}")