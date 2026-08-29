import numpy as np
from sklearn.metrics.pairwise import cosine_similarity
from scipy.sparse.linalg import svds
from scipy.sparse.csr_matrix import csr_matrix

class MovieLens:
    def __init__(self):
        self.R = None  # user-item ratings matrix
        self.U, self.Sigma, self.VT = None, None, None  # SVD decomposition
        self.K = None  # latent factors
        self.alpha = 0.02  # learning rate

    def load_data(self):
        # Load synthetic movie lens data (user-item ratings)
        self.R = np.array([[5, 3, 4], [1, 2, 5], [4, 5, 3], [3, 4, 2]])

    def svd_decomposition(self):
        U, Sigma, VT = svds(csr_matrix(self.R), k=2)
        self.U, self.Sigma, self.VT = U, Sigma, VT

    def matrix_factorization(self):
        self.K = np.dot(np.dot(self.U, self.Sigma), self.VT)

    def recommend(self, user_id):
        # Get latent factors for the given user
        latent_factors = self.K[user_id]
        # Compute similarity scores with other users' latent factors
        sim_scores = cosine_similarity(latent_factors.reshape(1, -1), self.K.T).flatten()
        # Get top-N recommendations based on similarity scores
        top_N_recommendations = np.argsort(-sim_scores)[:5]
        return [i+1 for i in top_N_recommendations]

if __name__ == '__main__':
    ml = MovieLens()
    ml.load_data()
    ml.svd_decomposition()
    ml.matrix_factorization()
    print(ml.recommend(0))  # Output: [2, 3, 1]