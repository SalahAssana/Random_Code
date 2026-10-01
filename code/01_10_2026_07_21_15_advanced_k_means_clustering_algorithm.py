import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

class KMeansClustering:
    def __init__(self, k):
        self.k = k
        self.centroids = None
        self.labels = None

    def fit(self, X):
        self.centroids = KMeans(n_clusters=self.k).fit_predict(X)
        return self.centroids

    def predict(self, X):
        return KMeans(n_clusters=self.k).fit_predict(X)

    def plot_clusters(self, X):
        plt.scatter(X[:, 0], X[:, 1], c=self.labels)
        plt.scatter(self.centroids[:, 0], self.centroids[:, 1], marker='*', s=200, color='red')
        plt.show()

if __name__ == '__main__':
    np.random.seed(0)
    X = np.vstack((np.random.normal(0, 0.5, (1000, 2)),
                   np.random.normal(2, 0.5, (500, 2)),
                   np.random.normal(4, 0.5, (500, 2))))

    kmeans = KMeansClustering(k=3)
    centroids = kmeans.fit(X)
    labels = kmeans.predict(X)

    print(f"Centroids: {centroids}")
    print(f"Labels: {labels}")

    kmeans.plot_clusters(X)