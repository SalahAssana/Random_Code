import numpy as np
from sklearn.metrics.pairwise import cosine_similarity
from scipy.sparse.linalg import svds

class Recommender:
    def __init__(self, ratings):
        self.ratings = ratings
        self.num_users, self.num_items = ratings.shape

    def matrix_factorization(self, num_factors=20, regularization=0.01):
        # Initialize U and V matrices with random values
        U = np.random.rand(self.num_users, num_factors)
        V = np.random.rand(self.num_items, num_factors)

        # Compute the latent factors for each user and item
        for i in range(num_factors):
            U[:, i] = svds(self.ratings, k=i)[0].T
            V[:, i] = svds(self.ratings.T, k=i)[0].T

        return U, V

    def get_recommendations(self, user_id, num_items=5):
        # Compute the latent factors for the given user
        U, _ = self.matrix_factorization()
        user_factors = U[user_id]

        # Compute the similarity between the given user and all items
        similarities = cosine_similarity([user_factors], V)[0]

        # Get the top N recommendations
        top_items = np.argsort(-similarities)[:num_items]
        return [(i, self.ratings[user_id][i]) for i in top_items]

def generate_synthetic_ratings(num_users=100, num_items=500, density=0.1):
    ratings = np.random.rand(num_users, num_items)
    ratings[ratings < density] = 0
    ratings[ratings >= density] = 1
    return ratings

if __name__ == '__main__':
    # Generate synthetic ratings
    ratings = generate_synthetic_ratings()

    # Create a recommender instance
    recommender = Recommender(ratings)

    # Get recommendations for user 42
    print("Recommendations for user 42:")
    for item, score in recommender.get_recommendations(42):
        print(f"{item}: {score}")