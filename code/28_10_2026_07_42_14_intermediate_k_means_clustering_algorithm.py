import numpy as np
import matplotlib.pyplot as plt

class KMeans:
    def __init__(self, k=2, max_iters=1000):
        self.k = k
        self.max_iters = max_iters
        self.cluster_centers_ = None

    def fit(self, X):
        n_samples, n_features = X.shape
        np.random.seed(0)
        initial_indices = np.random.choice(n_samples, self.k, replace=False)
        self.cluster_centers_ = X[initial_indices]

        for _ in range(self.max_iters):
            labels = self._predict(X)
            if (labels == -1).all():
                break

            new_centers = np.zeros_like(self.cluster_centers_)
            for k in range(self.k):
                cluster_points = X[labels == k]
                if len(cluster_points) > 0:
                    new_center = np.mean(cluster_points, axis=0)
                    new_centers[k] = new_center

            self.cluster_centers_ = new_centers

    def _predict(self, X):
        labels = -1 * np.ones(len(X))
        for i in range(len(X)):
            distances = [np.linalg.norm(X[i] - center) for center in self.cluster_centers_]
            label = np.argmin(distances)
            labels[i] = label
        return labels

    def predict(self, X):
        return self._predict(X)

    def plot_clusters(self, X, y=None):
        colors = ['r', 'g', 'b']
        fig = plt.figure()
        ax = fig.add_subplot(111)
        if not y is None:
            for i in range(self.k):
                points = X[y == i]
                ax.scatter(*points.T, c=colors[i], marker='o')
        else:
            for i in range(self.k):
                cluster_points = self.cluster_centers_[i]
                ax.scatter(cluster_points[0], cluster_points[1], c='k', marker='*', s=100)

        plt.show()

if __name__ == '__main__':
    X = np.array([[2, 3], [5, 4], [9, 6], [11, 10], [13, 12]])
    kmeans = KMeans(k=3)
    kmeans.fit(X)
    kmeans.predict(X)
    kmeans.plot_clusters(X)