#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import warnings

def kmeans_clustering(X, k):
    """
    Perform K-Means clustering on the input data X with k clusters.

    Parameters:
    - X (numpy array): The input data.
    - k (int): The number of clusters.

    Returns:
    - labels (numpy array): The cluster assignments for each data point.
    - centroids (numpy array): The coordinates of the cluster centers.
    """
    # Perform K-Means clustering
    kmeans = KMeans(n_clusters=k)
    kmeans.fit(X)

    # Get the cluster assignments and centroids
    labels = kmeans.labels_
    centroids = kmeans.cluster_centers_

    return labels, centroids

def plot_data_and_centroids(X, labels, centroids):
    """
    Plot the input data and the cluster centers.

    Parameters:
    - X (numpy array): The input data.
    - labels (numpy array): The cluster assignments for each data point.
    - centroids (numpy array): The coordinates of the cluster centers.
    """
    # Create a 3D plot
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Plot the input data
    ax.scatter(X[:, 0], X[:, 1], X[:, 2], c=labels)

    # Plot the cluster centers
    ax.scatter(centroids[:, 0], centroids[:, 1], centroids[:, 2])

    plt.show()

if __name__ == '__main__':
    # Generate synthetic data
    np.random.seed(0)
    X = np.random.rand(100, 3)

    # Perform K-Means clustering with k=5 clusters
    labels, centroids = kmeans_clustering(X, 5)

    # Plot the input data and the cluster centers
    plot_data_and_centroids(X, labels, centroids)