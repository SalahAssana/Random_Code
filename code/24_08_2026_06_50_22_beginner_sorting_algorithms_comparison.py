import random
import matplotlib.pyplot as plt
import numpy as np

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i-1
        while j >=0 and key < arr[j] :
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = key
    return arr

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr)//2
    left_half = arr[:mid]
    right_half = arr[mid:]
    return merge(merge_sort(left_half), merge_sort(right_half))

def merge(left, right):
    merged = []
    left_index = 0
    right_index = 0
    while left_index < len(left) and right_index < len(right):
        if left[left_index] <= right[right_index]:
            merged.append(left[left_index])
            left_index += 1
        else:
            merged.append(right[right_index])
            right_index += 1
    merged.extend(left[left_index:])
    merged.extend(right[right_index:])
    return merged

# Synthetic data generation
data = [random.randint(0,100) for _ in range(20)]
print("Unsorted data:", data)

# Sorting and timing
bubble_sort_data = bubble_sort(data.copy())
insertion_sort_data = insertion_sort(data.copy())
merge_sort_data = merge_sort(data.copy())

print("\nSorted data using Bubble Sort:", bubble_sort_data)
print("Sorted data using Insertion Sort:", insertion_sort_data)
print("Sorted data using Merge Sort:", merge_sort_data)

# Plotting the results
plt.figure(figsize=(10,4))
plt.subplot(1,3,1)
plt.plot(data)
plt.title('Unsorted Data')
plt.subplot(1,3,2)
plt.plot(bubble_sort_data)
plt.title('Bubble Sort')
plt.subplot(1,3,3)
plt.plot(insertion_sort_data)
plt.title('Insertion Sort')
plt.show()