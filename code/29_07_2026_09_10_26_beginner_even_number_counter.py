# Even Number Counter

def even_numbers(lst):
    # Initialize an empty list to store even numbers
    even_nums = []
    
    # Iterate over each number in the input list
    for num in lst:
        # Check if the number is even (i.e., divisible by 2)
        if num % 2 == 0:
            # If it's even, add it to the 'even_nums' list
            even_nums.append(num)
    
    # Return the list of even numbers
    return even_nums

# Synthetic data for testing
numbers = [1, 3, 4, 5, 6, 7, 8, 9, 10]

if __name__ == '__main__':
    # Call the 'even_numbers' function with the test data
    result = even_numbers(numbers)
    
    # Print the list of even numbers
    print("Even Numbers:", result)