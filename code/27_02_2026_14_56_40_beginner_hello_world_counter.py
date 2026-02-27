# Hello World Counter
def hello_world_counter(input_string):
    # Initialize count to 0
    count = 0
    
    # Loop through each word in the input string
    for word in input_string.split():
        # Check if the word is 'Hello'
        if word.lower() == 'hello':
            # Increment the count
            count += 1
    
    # Return the count
    return count

# Test the function with a sample input
input_string = "Hello world, Hello again, Goodbye!"
print("Count of 'Hello':", hello_world_counter(input_string))

if __name__ == '__main__':
    pass