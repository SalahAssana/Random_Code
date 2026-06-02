# Guessing Game
import random

low = 1
high = 100

print("Welcome to the guessing game!")
print("I'm thinking of a number between", low, "and", high)

while True:
    guess = int(input("Guess a number: "))
    
    if guess < low or guess > high:
        print("Invalid input! Please enter a number within the range.")
    elif guess == random.randint(low, high):
        print(" Congratulations! You guessed it!")
        break
    else:
        print("Too high" if guess > random.randint(low, high) else "Too low")