def binary_search(arr, target):
    low = 0
    high = len(arr) - 1
    
    while low <= high:
        mid = (low + high) // 2
        
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            low = mid + 1
        else:
            high = mid - 1
    
    return -1

if __name__ == '__main__':
    array = [i for i in range(100)]
    array.sort()
    
    target = 50
    
    result = binary_search(array, target)
    
    if result != -1:
        print(f"Target {target} found at index {result}.")
    else:
        print(f"Target {target} not found.")