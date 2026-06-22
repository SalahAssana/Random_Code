# Guessing Game
import random

low = 1
high = 100

print("Think of a number between", low, "and", high)
print("I'll try to guess it!")

guess = int((high + low) / 2)

while True:
    response = input("Is your number higher or lower than " + str(guess) + "? (higher/lower/youwin): ")
    
    if response.lower() == 'youwin':
        print("Yay! I guessed it!")
        break
    elif response.lower() == 'higher':
        low = guess + 1
        guess = int((high + low) / 2)
    elif response.lower() == 'lower':
        high = guess - 1
        guess = int((high + low) / 2)

if __name__ == '__main__':
    pass