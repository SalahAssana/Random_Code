import random

# Initialize a random number to guess
target_number = random.randint(1, 100)

# Set the number of attempts allowed
attempts_allowed = 6

print("Welcome to Guess My Number!")
print("I'm thinking of a number between 1 and 100.")
print("You have {} attempts to guess it.".format(attempts_allowed))

while attempts_allowed > 0:
    # Ask the user for their guess
    user_guess = int(input("Enter your guess: "))
    
    # Check if the user's guess is correct
    if user_guess == target_number:
        print("Congratulations! You guessed my number correctly!")
        break
    
    # If not, decrement the attempts allowed and provide feedback
    else:
        attempts_allowed -= 1
        if user_guess < target_number:
            print("Too low! Try a higher number.")
        else:
            print("Too high! Try a lower number.")
    
if attempts_allowed == 0:
    print("Sorry, you didn't guess my number. It was {}.".format(target_number))

if __name__ == '__main__':
    pass