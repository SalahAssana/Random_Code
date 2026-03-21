import random
import matplotlib.pyplot as plt
import numpy as np

def swap(arr, i, j):
    arr[i], arr[j] = arr[j], arr[i]

def bubble_sort(arr):
    n = len(arr)
    for i in range(n-1):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                swap(arr, j, j+1)

def generate_random_array(size):
    return [random.randint(0, 100) for _ in range(size)]

def visualize_bubble_sort(size):
    arr = generate_random_array(size)
    sorted_arr = [x[:] for x in [[arr]]]
    
    plt.ion()
    fig, ax = plt.subplots()
    line, = ax.plot(sorted_arr[0])
    ax.set_ylim(0, 101)

    for i in range(len(arr)):
        bubble_sort(arr[:])
        line.set_ydata(arr)
        plt.draw()
        plt.pause(.1)
        
    plt.ioff()
    plt.show()

if __name__ == '__main__':
    visualize_bubble_sort(20)