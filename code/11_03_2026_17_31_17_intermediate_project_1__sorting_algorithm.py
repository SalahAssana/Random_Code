# Project 1: Sorting Algorithm
# Python Implementation

def merge_sort(arr):
    # Base case: If the array has one or zero elements, it's already sorted
    if len(arr) <= 1:
        return arr
    
    # Divide the array into two halves
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    
    # Recursively sort both halves
    left_half = merge_sort(left_half)
    right_half = merge_sort(right_half)
    
    # Merge the sorted halves
    return merge(left_half, right_half)


def merge(left, right):
    # Initialize an empty list to store the merged result
    merged = []
    i = j = 0
    
    # Compare elements from both arrays and add the smaller one to the merged array
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1
    
    # Add any remaining elements from either array
    merged.extend(left[i:])
    merged.extend(right[j:])
    
    return merged


# Test the merge sort algorithm
if __name__ == '__main__':
    import random

    # Generate a list of random integers for testing
    arr = [random.randint(1, 100) for _ in range(20)]
    print("Original array:", arr)
    
    sorted_arr = merge_sort(arr)
    print("Sorted array:", sorted_arr)