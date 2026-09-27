import networkx as nx
import community as cm
from scipy.spatial.distance import pdist, squareform
from sklearn.cluster import KMeans
import numpy as np
import matplotlib.pyplot as plt

class SocialNetworkAnalyzer:
    def __init__(self, G):
        self.G = G

    def calculate_communities(self):
        # Use the Louvain algorithm for community detection
        partition = cm.best_partition(self.G)
        return partition

    def visualize_network(self, communities):
        # Visualize the network with community colors
        pos = nx.spring_layout(self.G)
        plt.figure(figsize=(10, 8))
        nx.draw_networkx(self.G, pos, node_color=list(map(str, communities)), cmap=plt.cm.rainbow, node_size=500, arrows=False)
        plt.show()

    def calculate_clustering_coefficients(self):
        # Calculate the clustering coefficient for each community
        clusters = []
        for community in set(communities.values()):
            nodes_in_community = [node for node, cluster_id in communities.items() if cluster_id == community]
            G_cluster = self.G.subgraph(nodes_in_community)
            clustering_coefficient = nx.average_clustering(G_cluster)
            clusters.append(clustering_coefficient)

        return clusters

    def analyze_network(self):
        # Calculate the Louvain communities
        communities = self.calculate_communities()

        # Visualize the network with community colors
        self.visualize_network(communities)

        # Calculate the clustering coefficients for each community
        clustering_coefficients = self.calculate_clustering_coefficients()

        return communities, clustering_coefficients

def main():
    # Load the social network data (e.g., from a file or database)
    G = nx.from_pandas_dataframe(pd.read_csv('social_network_data.csv', header=None), 0, 1)

    analyzer = SocialNetworkAnalyzer(G)

    # Perform the analysis
    communities, clustering_coefficients = analyzer.analyze_network()

    print("Communities:", communities)
    print("Clustering Coefficients:", clustering_coefficients)

if __name__ == '__main__':
    main()