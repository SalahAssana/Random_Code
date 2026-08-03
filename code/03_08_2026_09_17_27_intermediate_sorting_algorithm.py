def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

def quicksort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr)//2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quicksort(left) + middle + quicksort(right)

def main():
    import random

    # Generate a list of 20 random numbers
    data = [random.randint(0, 100) for _ in range(20)]

    print("Original list:", data)

    bubble_sorted_data = bubble_sort(data.copy())
    print("Bubble sorted:", bubble_sorted_data)

    quick_sorted_data = quicksort(data.copy())
    print("Quick sorted:", quick_sorted_data)

if __name__ == '__main__':
    main()