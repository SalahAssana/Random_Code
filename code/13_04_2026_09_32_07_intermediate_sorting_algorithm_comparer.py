import random
import matplotlib.pyplot as plt
import time

# Define constants
ALGORITHMS = ['Bubble Sort', 'Quick Sort']
DATASET_SIZE = 1000
MIN_VALUE = 1
MAX_VALUE = 100

def generate_random_dataset(size):
    """Generate a random dataset of integers"""
    return [random.randint(MIN_VALUE, MAX_VALUE) for _ in range(size)]

def bubble_sort(dataset):
    """Implement Bubble Sort algorithm"""
    n = len(dataset)
    for i in range(n):
        for j in range(0, n - i - 1):
            if dataset[j] > dataset[j + 1]:
                dataset[j], dataset[j + 1] = dataset[j + 1], dataset[j]
    return dataset

def quick_sort(dataset):
    """Implement Quick Sort algorithm"""
    if len(dataset) <= 1:
        return dataset
    pivot = dataset[0]
    less = [x for x in dataset[1:] if x < pivot]
    equal = [x for x in dataset if x == pivot]
    greater = [x for x in dataset[1:] if x > pivot]
    return quick_sort(less) + equal + quick_sort(greater)

def time_algorithm(algorithm, dataset):
    """Measure the execution time of an algorithm"""
    start_time = time.time()
    algorithm(dataset)
    end_time = time.time()
    return end_time - start_time

def plot_algorithm_performance():
    """Plot the performance of different algorithms"""
    datasets = [generate_random_dataset(DATASET_SIZE) for _ in range(3)]
    times = {algorithm: [] for algorithm in ALGORITHMS}
    
    # Run and measure each algorithm
    for dataset in datasets:
        for algorithm in ALGORITHMS:
            if algorithm == 'Bubble Sort':
                times[algorithm].append(time_algorithm(bubble_sort, dataset.copy()))
            elif algorithm == 'Quick Sort':
                times[algorithm].append(time_algorithm(quick_sort, dataset.copy()))

    # Plot the results
    plt.bar(ALGORITHMS, [sum(times[algorithm]) for algorithm in ALGORITHMS])
    plt.xlabel('Algorithm')
    plt.ylabel('Execution Time (seconds)')
    plt.title('Sorting Algorithm Performance')
    plt.show()

if __name__ == '__main__':
    plot_algorithm_performance()