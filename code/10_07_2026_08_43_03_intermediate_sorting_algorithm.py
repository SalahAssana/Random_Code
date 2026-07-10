def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def main():
    if __name__ == '__main__':
        # Generate synthetic data
        import random
        arr = [random.randint(0, 100) for _ in range(20)]
        print("Original array:", arr)
        
        sorted_arr = bubble_sort(arr.copy())
        print("Sorted array:", sorted_arr)

if __name__ == '__main__':
    main()