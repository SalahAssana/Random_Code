import numpy as np
from scipy.optimize import minimize
import matplotlib.pyplot as plt

class OptimizationAlgorithmSimulator:
    def __init__(self):
        self.algorithms = {
            "Gradient Descent": self.gradient_descent,
            "Simulated Annealing": self.simulated_annealing,
            "Conjugate Gradient": self.conjugate_gradient
        }

    def gradient_descent(self, x0, f, df, max_iter=1000):
        x = x0.copy()
        for _ in range(max_iter):
            x -= 0.01 * df(x)
            if np.linalg.norm(df(x)) < 1e-6:
                return x
        return x

    def simulated_annealing(self, x0, f, df, T=1000, alpha=0.9, max_iter=10000):
        x = x0.copy()
        for _ in range(max_iter):
            dx = np.random.normal(0, 1, len(x))
            new_x = x + alpha * dx
            if f(new_x) < f(x):
                x = new_x
            else:
                p = np.exp((f(x) - f(new_x)) / T)
                if np.random.rand() < p:
                    x = new_x
            T *= alpha
        return x

    def conjugate_gradient(self, x0, f, df, max_iter=100):
        x = x0.copy()
        g = df(x)
        p = -g.copy()
        for _ in range(max_iter):
            g_p = np.dot(g, p)
            if g_p < 1e-6:
                return x
            a = 1
            b = f(x + a * p) - f(x)
            while b > 0:
                a *= 0.5
                b = f(x + a * p) - f(x)
            x += a * p
            g_new = df(x)
            b = np.dot(g_new, p)
            if b > 0.5 or g_p <= 0:
                p = -g_new.copy()
            else:
                c = (1 + np.sqrt(1 + 4 * a * b)) / 2
                s = (a * b) / (c * (c - 1))
                t = (1 - c) * (x + a * p)
                x = x + a * p + (t - x)
            g_p = np.dot(g_new, p)
        return x

    def run_simulation(self):
        def f(x): return np.sum((x - 2)**2)
        def df(x): return 2 * (x - 2)

        x0 = np.array([1.5])

        results = {}
        for name, algorithm in self.algorithms.items():
            x = algorithm(x0, f, df)
            results[name] = x

        plt.plot([f(x) for x in results.values()])
        plt.xlabel('Algorithm')
        plt.ylabel('Cost Function Value')
        plt.title('Optimization Algorithm Comparison')
        plt.show()

if __name__ == '__main__':
    simulator = OptimizationAlgorithmSimulator()
    simulator.run_simulation()