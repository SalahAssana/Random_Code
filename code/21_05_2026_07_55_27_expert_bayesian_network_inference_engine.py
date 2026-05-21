import numpy as np
from scipy.stats import norm
from sklearn.metrics.pairwise import pairwise_distances

class BayesianNetwork:
    def __init__(self):
        self.nodes = {}
        self.edges = []

    def add_node(self, node_id, parent_ids=None):
        if parent_ids is None:
            parent_ids = []
        self.nodes[node_id] = {'parent_ids': parent_ids, 'cpd': {}}

    def add_edge(self, from_node, to_node):
        self.edges.append((from_node, to_node))

    def infer(self, node_id):
        node = self.nodes[node_id]
        if not node['parent_ids']:
            return 0.5  # uniform prior
        evidence = {k: v for k, v in self.nodes.items() if k != node_id and self.nodes[k]['parent_ids'] == []}
        likelihoods = []
        for parent_node_id, value in zip(node['parent_ids'], [evidence.get(parent_node_id, {}).get('value', None) for _ in range(len(node['parent_ids']))]):
            if value is not None:
                likelihoods.append(norm.cdf(value, loc=0, scale=1))
            else:
                likelihoods.append(1)
        return np.prod(np.array(likelihoods))

    def infer_all(self):
        evidence = {k: v for k, v in self.nodes.items() if k != 'root' and self.nodes[k]['parent_ids'] == []}
        max_likelihood = 0
        best_node_id = None
        for node_id, node in self.nodes.items():
            if not node['parent_ids']:
                continue
            likelihood = self.infer(node_id)
            if likelihood > max_likelihood:
                max_likelihood = likelihood
                best_node_id = node_id
        return best_node_id

if __name__ == '__main__':
    bn = BayesianNetwork()
    bn.add_node('root', parent_ids=[])
    bn.add_node('A', parent_ids=['root'])
    bn.add_node('B', parent_ids=['root'])
    bn.add_edge('root', 'A')
    bn.add_edge('root', 'B')
    evidence = {'root': 0.5}
    inferred_node_id = bn.infer_all()
    print(inferred_node_id)