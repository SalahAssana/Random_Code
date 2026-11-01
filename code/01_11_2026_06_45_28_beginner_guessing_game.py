# Guessing Game
# A simple game that asks for user input and keeps track of score.

score = 0

print("Welcome to the Guessing Game!")
print("I'm thinking of a number between 1 and 100.")

while True:
    guess = int(input("What's your guess? "))
    
    if guess < 1 or guess > 100:
        print("Invalid input. Please enter a number between 1 and 100.")
    elif abs(guess - 50) <= 10:  # The correct answer is 50
        score += 1
        print(f"Correct! You scored {score} points.")
    else:
        print("Sorry, that's not the correct answer. Try again!")
    
    if input("Do you want to play again? (y/n) ").lower() != 'y':
        break

print(f"Game over! Your final score is {score}.")