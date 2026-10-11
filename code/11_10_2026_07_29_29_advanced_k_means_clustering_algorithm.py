import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
from sklearn.cluster import KMeans

class KMeansClustering:
    def __init__(self, k, max_iters=100):
        self.k = k
        self.max_iters = max_iters
        self.centroids = None
        self.labels = None

    def fit(self, X):
        self.centroids = np.random.rand(self.k, X.shape[1])
        for _ in range(self.max_iters):
            labels = self.predict(X)
            new_centroids = np.zeros((self.k, X.shape[1]))
            cluster_counts = [0] * self.k
            for x, label in zip(X, labels):
                cluster_counts[label] += 1
                new_centroids[label] += x
            for i in range(self.k):
                if cluster_counts[i] > 0:
                    new_centroids[i] /= cluster_counts[i]
            if np.all(self.centroids == new_centroids):
                break
            self.centroids = new_centroids

    def predict(self, X):
        distances = np.linalg.norm(X[:, None] - self.centroids[None], axis=2)
        return np.argmin(distances, axis=1)

    def visualize(self, X, labels):
        plt.scatter(X[:, 0], X[:, 1], c=labels)
        for i, centroid in enumerate(self.centroids):
            plt.scatter(centroid[0], centroid[1], marker='*', s=200, color=f"C{i}")
        plt.show()

if __name__ == '__main__':
    k = 3
    X, _ = make_blobs(n_samples=100, centers=k, cluster_std=0.5, random_state=0)
    clustering = KMeansClustering(k)
    clustering.fit(X)
    labels = clustering.predict(X)
    clustering.visualize(X, labels)