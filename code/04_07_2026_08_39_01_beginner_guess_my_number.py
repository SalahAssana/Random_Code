import random

# Set the range of possible numbers
min_num = 1
max_num = 100

# Generate a random number within the range
target_number = random.randint(min_num, max_num)

print("Welcome to Guess My Number!")
print(f"I'm thinking of a number between {min_num} and {max_num}.")
print("You have to guess the number. After each guess, I'll give you a hint.")
print("If your guess is higher than my number, I'll say 'Too high.'")
print("If your guess is lower than my number, I'll say 'Too low.'")

while True:
    # Get the user's guess
    user_guess = int(input("Enter your guess: "))

    if user_guess < target_number:
        print("Too low.")
    elif user_guess > target_number:
        print("Too high.")
    else:
        print(f"Congratulations! You guessed my number {target_number} correctly!")
        break

if __name__ == '__main__':
    pass