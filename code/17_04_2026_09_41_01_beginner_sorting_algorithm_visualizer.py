# Sorting Algorithm Visualizer
import random
import time
import matplotlib.pyplot as plt

# Bubble Sort Function
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

# Quicksort Function
def quicksort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quicksort(left) + middle + quicksort(right)

# Generate Random List
random_list = random.sample(range(1, 100), 10)
print("Original List:", random_list)

# Start Timer
start_time = time.time()

# Sort List Using Bubble Sort
bubble_sorted_list = bubble_sort(random_list[:])
print("Bubble Sorted List:", bubble_sorted_list)

# Calculate Time Taken by Bubble Sort
end_time = time.time()
bubble_sort_time = end_time - start_time
print("Time taken by Bubble Sort: ", bubble_sort_time, "seconds")

# Start Timer
start_time = time.time()

# Sort List Using Quicksort
quicksort_sorted_list = quicksort(random_list[:])
print("Quicksort Sorted List:", quicksort_sorted_list)

# Calculate Time Taken by Quicksort
end_time = time.time()
quicksort_time = end_time - start_time
print("Time taken by Quicksort: ", quicksort_time, "seconds")

# Plotting the original and sorted lists
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.bar(range(len(random_list)), random_list, color='b')
plt.title('Original List')

plt.subplot(1, 2, 2)
plt.bar(range(len(bubble_sorted_list)), bubble_sorted_list, color='r')
plt.title('Bubble Sorted List')

plt.tight_layout()
plt.show()

if __name__ == '__main__':
    pass