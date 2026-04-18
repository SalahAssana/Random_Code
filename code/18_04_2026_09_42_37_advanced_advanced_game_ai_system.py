import numpy as np
from sklearn.neural_network import MLPClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

class GameAI:
    def __init__(self):
        self.nn = None
        self.dt = None

    def train(self, X_train, y_train):
        # Train a neural network using the training data
        self.nn = MLPClassifier(hidden_layer_sizes=(10,), max_iter=1000)
        self.nn.fit(X_train, y_train)

        # Train a decision tree using the training data
        self.dt = DecisionTreeClassifier()
        self.dt.fit(X_train, y_train)

    def make_decision(self, X):
        # Use the neural network to make a prediction
        nn_pred = self.nn.predict(X)

        # Use the decision tree to make a prediction
        dt_pred = self.dt.predict(X)

        # Combine the predictions using a voting mechanism
        combined_pred = np.array([nn_pred[i] if nn_pred[i] == dt_pred[i] else -1 for i in range(len(nn_pred))])

        return combined_pred

# Synthetic data generation
np.random.seed(0)
X = np.concatenate((np.random.rand(100, 5), np.random.randn(100, 3)), axis=1)
y = np.array(['A', 'B', 'C', 'D', 'E', 'F'] * 10)
le = LabelEncoder()
y = le.fit_transform(y)

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Create an instance of the GameAI class
ai = GameAI()

# Train the AI using the training data
ai.train(X_train, y_train)

# Make decisions on the testing data
y_pred = ai.make_decision(X_test)

print("Accuracy:", accuracy_score(y_test, y_pred))
print("Classification Report:\n", classification_report(y_test, y_pred))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))

if __name__ == '__main__':