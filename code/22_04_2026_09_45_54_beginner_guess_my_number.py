# Guess My Number
# BEGINNER project: Create a game where the user thinks of a number between 1 and 100,
#                  and the program tries to guess it by asking yes or no questions.

low = 1
high = 100

while True:
    print(f"Think of a number between {low} and {high}.")
    print("I'll try to guess it with yes/no questions.")

    guess = (low + high) // 2
    print(f"My guess is: {guess}")

    response = input("Is your number higher or lower? (h/l): ")

    if response == 'h':
        low = guess + 1
    elif response == 'l':
        high = guess - 1
    else:
        print("Invalid input. Please enter 'h' for higher or 'l' for lower.")
        continue

    if low > high:
        break

print(f"Game over! Your number was {guess}.")