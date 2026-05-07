import random

# List of words to choose from
word_list = ["apple", "banana", "cherry", "date", "elderberry"]

def generate_word():
    """Returns a random word from the list"""
    return random.choice(word_list)

def get_guessed_word():
    """Asks user for input and returns the guessed letter"""
    while True:
        guess = input("Guess a letter: ")
        if len(guess) != 1 or not guess.isalpha():
            print("Invalid input. Please enter a single letter.")
        else:
            return guess

def update_guess(word, guessed_word):
    """Updates the word based on the guessed letter"""
    for i in range(len(word)):
        if word[i] == guessed_word:
            return word[:i] + guessed_word + word[i+1:]
    return word

def check_win(word, guessed_word):
    """Checks if the user has won or not"""
    if '_' not in guessed_word and all(letter in guessed_word for letter in word):
        print("Congratulations! You've guessed the word.")
        return True
    elif '_' in guessed_word:
        print("Keep trying!")
        return False

def main():
    """Main function to run the game"""
    word = generate_word()
    guessed_word = "_" * len(word)
    while True:
        print(guessed_word)
        guess = get_guessed_word()
        guessed_word = update_guess(word, guess)
        if check_win(word, guessed_word):
            break

if __name__ == '__main__':
    main()