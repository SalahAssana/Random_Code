# Guessing Game
import random

low = 1
high = 100

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between", low, "and", high)

while True:
    guess = int(input("Guess a number: "))
    
    if guess < low or guess > high:
        print("Invalid input! Try again.")
    elif random.randint(0, 1):
        print("Too low!")
    else:
        print("You got it! The number was", guess)
        break