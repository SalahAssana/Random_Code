import numpy as np
from sklearn.metrics.pairwise import cosine_similarity
from scipy.sparse.linalg import svds
from sklearn.preprocessing import normalize

class GraphBasedRecommendationSystem:
    def __init__(self, user_item_matrix):
        self.user_item_matrix = user_item_matrix
        self.num_users, self.num_items = self.user_item_matrix.shape

    def compute_user_factors(self, num_factors=50):
        # Compute latent factors for users using SVD
        U, sigma, Vt = svds(self.user_item_matrix.T, k=num_factors)
        return U * sigma[:, np.newaxis]

    def compute_item_factors(self, user_factors):
        # Compute latent factors for items using matrix factorization
        item_factors = self.user_item_matrix @ user_factors.T
        return normalize(item_factors, axis=0)

    def predict_user_ratings(self, user_id, num_recommendations=10):
        # Get the user's latent factors
        user_factors = self.compute_user_factors()
        user_vector = user_factors[user_id]

        # Compute similarity scores with all items
        item_factors = self.compute_item_factors(user_factors)
        similarities = cosine_similarity([user_vector], item_factors).flatten()

        # Rank items by similarity and return the top-N recommendations
        indices = np.argsort(-similarities)[:num_recommendations]
        return [item_idx for item_idx in indices if item_idx not in self.user_item_matrix[user_id].nonzero()[1]]

    def run(self):
        print("Recommendation System Running...")
        user_factors = self.compute_user_factors()
        print("User Factors Computed.")

        recommended_items = []
        for user_id in range(self.num_users):
            recommendations = self.predict_user_ratings(user_id)
            if len(recommendations) > 0:
                recommended_items.append((user_id, recommendations))

        print("Recommendations:")
        for user_id, items in recommended_items:
            print(f"User {user_id} recommends: {[item + 1 for item in items]}")

if __name__ == '__main__':
    # Synthetic data example
    num_users = 100
    num_items = 500
    user_item_matrix = np.random.randint(0, 2, size=(num_users, num_items))

    recommendation_system = GraphBasedRecommendationSystem(user_item_matrix)
    recommendation_system.run()