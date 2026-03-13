import networkx as nx
from collections import defaultdict
from heapq import heapify, heappop

class SocialNetworkAnalyzer:
    def __init__(self):
        self.graph = nx.Graph()

    def load_data(self, data_file):
        try:
            with open(data_file, 'r') as f:
                for line in f:
                    user1, user2 = map(int, line.strip().split(','))
                    self.graph.add_edge(user1, user2)
        except FileNotFoundError:
            print(f"File {data_file} not found.")
        except Exception as e:
            print(f"Error loading data: {e}")

    def compute_centrality_measures(self):
        centrality_measures = defaultdict(dict)

        # Betweenness Centrality
        bc = nx.betweenness_centrality(self.graph, weight='weight')
        for node in self.graph.nodes:
            centrality_measures['Betweenness'][node] = bc.get(node, 0)

        # Closeness Centrality
        cc = nx.closeness_centrality(self.graph)
        for node in self.graph.nodes:
            centrality_measures['Closeness'][node] = cc.get(node, 0)

        # PageRank
        pr = nx.pagerank(self.graph, alpha=0.85, personalization=None, max_iter=100)
        for node in self.graph.nodes:
            centrality_measures['PageRank'][node] = pr.get(node, 0)

        return centrality_measures

    def find_clusters(self):
        clusters = []
        visited = set()
        heap = [(0, next(iter(self.graph.nodes)))]

        while heap:
            score, node = heappop(heap)
            if node not in visited:
                cluster = [node]
                visited.add(node)

                for neighbor in self.graph.neighbors(node):
                    if neighbor not in visited:
                        heap.append((score + 1, neighbor))
                        cluster.append(neighbor)
                clusters.append(cluster)

        return clusters

    def analyze(self, data_file):
        self.load_data(data_file)
        centrality_measures = self.compute_centrality_measures()
        clusters = self.find_clusters()

        print("Centrality Measures:")
        for measure_type, nodes in centrality_measures.items():
            print(f"{measure_type}: {nodes}")

        print("\nClusters:")
        for cluster in clusters:
            print(cluster)

if __name__ == '__main__':
    analyzer = SocialNetworkAnalyzer()
    analyzer.analyze('social_network_data.txt')