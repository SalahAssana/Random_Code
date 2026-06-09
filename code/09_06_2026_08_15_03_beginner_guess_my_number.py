# Guess My Number - Beginner Level Python Program

low = 1
high = 1000

while True:
    guess = (high + low) // 2
    print(f"Is your number {guess}?")
    
    response = input("Enter 'h' if the number is higher, 'l' if it's lower, or 'y' if you've found the correct number: ")
    
    if response == 'y':
        print(f"I've guessed your number correctly! It was indeed {guess}.")
        break
    elif response == 'h':
        low = guess + 1
    elif response == 'l':
        high = guess - 1
    else:
        print("Invalid input. Please enter 'h', 'l', or 'y'.")