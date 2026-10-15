# Project 1: Binary Search Algorithm

def binary_search(arr, target):
    """
    This function performs a binary search on the given array for the target value.

    Args:
        arr (list): The list to be searched.
        target: The value to be found in the list.

    Returns:
        int: The index of the target value if it is present in the list, -1 otherwise.
    """
    low = 0
    high = len(arr) - 1

    while low <= high:
        mid = (low + high) // 2
        guess = arr[mid]

        if guess == target:
            return mid
        elif guess > target:
            high = mid - 1
        else:
            low = mid + 1

    return -1


# Example usage:

arr = [2, 3, 4, 10, 40]
target = 10

index = binary_search(arr, target)

if index != -1:
    print("Target found at index", index)
else:
    print("Target not found in the array")