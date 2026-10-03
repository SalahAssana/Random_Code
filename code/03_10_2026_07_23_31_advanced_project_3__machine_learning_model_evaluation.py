from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score
import numpy as np
from collections import defaultdict
class ModelEvaluator:
    def __init__(self):
        self.metrics = defaultdict(list)

    def evaluate(self, predictions, labels):
        for prediction, label in zip(predictions, labels):
            if label == 0:
                self.metrics['true_negative'].append(1)
                self.metrics['false_positive'].append(0)
            else:
                self.metrics['true_positive'].append(1)
                self.metrics['false_negative'].append(0)

    def get_accuracy(self):
        true_positives = sum(self.metrics['true_positive'])
        false_negatives = len(self.metrics['false_negative'])
        true_negatives = sum(self.metrics['true_negative'])
        false_positives = len(self.metrics['false_positive'])
        accuracy = (true_positives + true_negatives) / (true_positives + true_negatives + false_negatives + false_positives)
        return accuracy

    def get_precision(self):
        true_positives = sum(self.metrics['true_positive'])
        false_positives = len(self.metrics['false_positive'])
        precision = true_positives / (true_positives + false_positives) if true_positives + false_positives > 0 else 0
        return precision

    def get_recall(self):
        true_positives = sum(self.metrics['true_positive'])
        false_negatives = len(self.metrics['false_negative'])
        recall = true_positives / (true_positives + false_negatives) if true_positives + false_negatives > 0 else 0
        return recall

    def get_f1_score(self):
        precision = self.get_precision()
        recall = self.get_recall()
        f1 = 2 * precision * recall / (precision + recall) if precision + recall > 0 else 0
        return f1

def main():
    evaluator = ModelEvaluator()
    predictions = [1, 1, 0, 0, 1, 1, 0, 0]
    labels = [1, 1, 0, 0, 1, 1, 0, 0]
    evaluator.evaluate(predictions, labels)
    accuracy = evaluator.get_accuracy()
    precision = evaluator.get_precision()
    recall = evaluator.get_recall()
    f1 = evaluator.get_f1_score()
    print(f"Accuracy: {accuracy:.2f}")
    print(f"Precision: {precision:.2f}")
    print(f"Recall: {recall:.2f}")
    print(f"F1 Score: {f1:.2f}")

if __name__ == '__main__':
    main()