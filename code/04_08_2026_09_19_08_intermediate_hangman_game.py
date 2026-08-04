import random

# List of words to guess from
word_list = ["apple", "banana", "cherry", "date", "elderberry"]

def get_random_word(word_list):
    """Return a random word from the list"""
    return random.choice(word_list)

def draw_hangman(attempts):
    """Draw hangman based on number of attempts"""
    if attempts == 6:
        print(" _______")
        print("|       |")
        print("|   O   |")
        print("| /|\  |")
        print("| / \  |")
        print("|_______|")
    elif attempts == 5:
        print(" _______")
        print("|       |")
        print("|   O   |")
        print("| /|\  |")
        print("|     |")
        print("|_______|")
    elif attempts == 4:
        print(" _______")
        print("|       |")
        print("|   O   |")
        print("| /|\  |")
        print("|    |")
        print("|_______|")
    elif attempts == 3:
        print(" _______")
        print("|       |")
        print("|   O   |")
        print("| /|\  |")
        print("|   |")
        print("|_______|")
    elif attempts == 2:
        print(" _______")
        print("|       |")
        print("|   O   |")
        print("| /|\  |")
        print("|  _|")
        print("|_______|")
    elif attempts == 1:
        print(" _______")
        print("|       |")
        print("|   O   |")
        print("| /|\  |")
        print("| _  |")
        print("|_______|")

def play_hangman():
    """Play the hangman game"""
    word = get_random_word(word_list)
    attempts = 6
    guessed_word = ["_"] * len(word)

    while True:
        print(" ".join(guessed_word))
        draw_hangman(attempts)
        
        guess = input("Guess a letter: ")
        
        if len(guess) != 1 or not guess.isalpha():
            print("Invalid input. Please enter a single letter.")
        elif guess in word:
            for i, letter in enumerate(word):
                if letter == guess:
                    guessed_word[i] = guess
            if "_" not in guessed_word:
                print(" ".join(guessed_word))
                print("Congratulations! You won!")
                return
        else:
            attempts -= 1
            print(f"Incorrect. {attempts} attempts left.")
            
        if attempts == 0:
            print("Game over. The word was: " + word)
            return

if __name__ == '__main__':
    play_hangman()