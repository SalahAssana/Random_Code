import numpy as np

class NeuralNetwork:
    def __init__(self, x, y):
        self.input      = x
        self.weights1   = np.random.rand(self.input.shape[1],4) 
        self.weights2   = np.random.rand(4,1)                 
        self.y          = y
        self.output     = np.zeros(self.y.shape)

    def feedforward(self):
        self.hidden_layer  = sigmoid(np.dot(self.input, self.weights1))
        self.output       = sigmoid(np.dot(self.hidden_layer, self.weights2))

    def backprop(self):
        d_weights2 = np.dot(self.hidden_layer.T, (2*(self.y - self.output)*sigmoid_derivative(self.output)))
        d_weights1 = np.dot(self.input.T,  (2*(self.y - self.output)*sigmoid_derivative(self.hidden_layer)*self.weights2.T))
        
        self.weights1 += d_weights1
        self.weights2 += d_weights2

def sigmoid(x):
    return 1/(1+np.exp(-x))

def sigmoid_derivative(x):
    return x*(1-x)

if __name__ == '__main__':
    X = np.array([[0,0,1],
                 [0,1,1],
                 [1,0,1],
                 [1,1,1]])
    
    y = np.array([[0],[1],[1],[0]]
    
    nn = NeuralNetwork(X,y)
    
    for i in range(1500):
        nn.feedforward()
        nn.backprop()

    print(nn.output)