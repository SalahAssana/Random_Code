import numpy as np
from scipy.optimize import minimize
import matplotlib.pyplot as plt

class OptimizationAlgorithm:
    def __init__(self, func, x0):
        self.func = func
        self.x0 = x0
        self.result = None

    def optimize(self):
        raise NotImplementedError("Subclasses must implement this method")

class GradientDescent(OptimizationAlgorithm):
    def optimize(self):
        x = np.array(self.x0)
        step_size = 0.1
        for _ in range(1000):
            gradient = self.func.gradient(x)
            x -= step_size * gradient
        return self.func(x)

class ConjugateGradient(OptimizationAlgorithm):
    def optimize(self):
        x = np.array(self.x0)
        gprev = None
        step_size = 0.1
        for _ in range(1000):
            g = self.func.gradient(x)
            if gprev is not None:
                b = np.dot(gprev, (g - gprev))
                step_size *= abs(b) / np.dot(g, g)
            s = -g
            e = 1e-10
            while np.dot(s, s) > e and abs(step_size) > e:
                a = np.dot(g, s)
                if a < 0:
                    t = -a
                else:
                    t = b / a
                s = s + t * gprev
                gprev = g
                g = self.func.gradient(x + step_size * s)
            x += step_size * s
        return self.func(x)

class QuasiNewton(OptimizationAlgorithm):
    def optimize(self):
        x = np.array(self.x0)
        B = np.eye(len(x))
        for _ in range(1000):
            g = self.func.gradient(x)
            x -= np.dot(np.linalg.inv(B), g)
            s = -g
            y = g
            for _ in range(10):
                s1 = np.dot(B, s)
                t = np.dot(s1, s) / np.dot(s1, s1)
                m = (np.dot(y, s) / np.dot(s1, s1)) * s - t * y
                B -= np.outer((np.dot(m, s1)), m) / np.dot(s1, s1)
                s = y
                y = self.func.gradient(x + np.dot(np.linalg.inv(B), s))
        return self.func(x)

class Rosenbrock:
    def __init__(self):
        pass

    def func(self, x):
        a = 100 * (x[1] - x[0]**2)
        b = (1 - x[0])**2
        return np.array([a + b])

    def gradient(self, x):
        g0 = -200 * (x[0]**2 - x[1]) + 2 * (1 - x[0])
        g1 = 100 * (x[1] - x[0]**2)
        return np.array([g0, g1])

def main():
    rosenbrock = Rosenbrock()
    algorithms = [GradientDescent(rosenbrock, np.array([-1.2])), ConjugateGradient(rosenbrock, np.array([-1.2])), QuasiNewton(rosenbrock, np.array([-1.2]))]
    results = []
    for algorithm in algorithms:
        result = algorithm.optimize()
        results.append(result)
    plt.plot([result[0] for result in results], [result[1] for result in results])
    plt.show()

if __name__ == '__main__':
    main()