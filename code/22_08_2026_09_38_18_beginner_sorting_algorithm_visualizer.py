import matplotlib.pyplot as plt
import random
import time

# Function to generate random list of numbers
def generate_random_list(length):
    return [random.randint(0, 100) for _ in range(length)]

# Bubble sort algorithm
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

# Function to visualize the sorting process
def visualize_sorting(arr):
    fig, ax = plt.subplots()
    x = range(len(arr))
    y = [i for i in arr]
    
    # Plot original array
    ax.plot(x, y, 'bo')
    ax.set_title('Original Array')
    ax.set_xlabel('Index')
    ax.set_ylabel('Value')
    
    # Sort the array and plot each step
    sorted_arr = bubble_sort(arr)
    for i in range(len(sorted_arr)):
        ax.clear()
        ax.plot(x, [i if j <= i else arr[j] for j in x], 'bo')
        ax.set_title(f'Step {i}')
        plt.pause(0.1)

# Main function
if __name__ == '__main__':
    # Generate a random list of 20 numbers
    arr = generate_random_list(20)
    
    # Start timer
    start_time = time.time()
    
    # Visualize the sorting process
    visualize_sorting(arr)
    
    # Stop timer and print execution time
    end_time = time.time()
    print(f'Execution Time: {end_time - start_time} seconds')