# Guess My Number - Beginner Level Project

LOW = 1
HIGH = 100

def binary_search():
    print("Think of a number between {} and {}".format(LOW, HIGH))
    while True:
        GUESS = (HIGH + LOW) // 2
        print("Is your number {}?".format(GUESS))
        response = input("(higher/lower/yes): ")
        if response == "yes":
            print("I guessed it! Your number was {}".format(GUESS))
            break
        elif response == "higher":
            LOW = GUESS + 1
        elif response == "lower":
            HIGH = GUESS - 1

if __name__ == '__main__':
    binary_search()