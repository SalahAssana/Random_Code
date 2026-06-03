# Hangman Game
import random

class Hangman:
    def __init__(self):
        self.word_list = ["apple", "banana", "cherry", "date", "elderberry"]
        self.word = random.choice(self.word_list)
        self.guessed_word = ["_"] * len(self.word)
        self.attempts = 6
        self.guessed_letters = []

    def print_hangman(self):
        if self.attempts == 6:
            print("   _______")
            print("  /       \\")
            print(" /         \\")
            print("|           |")
            print("|           |")
            print("|           |")
            print("|           |")
            print("|           |")
            print("  \___/    ")
        elif self.attempts == 5:
            print("   _______")
            print("  /       \\")
            print(" /         \\")
            print("|           |")
            print("|   o      |")
            print("|           |")
            print("|           |")
            print("|           |")
            print("  \___/    ")
        elif self.attempts == 4:
            print("   _______")
            print("  /       \\")
            print(" /         \\")
            print("|           |")
            print("|   o      |")
            print("|   |     |")
            print("|           |")
            print("|           |")
            print("  \___/    ")
        elif self.attempts == 3:
            print("   _______")
            print("  /       \\")
            print(" /         \\")
            print("|           |")
            print("|   o      |")
            print("|   |/     |")
            print("|           |")
            print("|           |")
            print("  \___/    ")
        elif self.attempts == 2:
            print("   _______")
            print("  /       \\")
            print(" /         \\")
            print("|           |")
            print("|   o      |")
            print("|   |/     |")
            print("|  /|     |")
            print("|           |")
            print("  \___/    ")
        elif self.attempts == 1:
            print("   _______")
            print("  /       \\")
            print(" /         \\")
            print("|           |")
            print("|   o      |")
            print("|   |/     |")
            print("|  /|\\   |")
            print("|           |")
            print("  \___/    ")

    def check_guess(self, letter):
        if letter in self.word:
            for i in range(len(self.word)):
                if self.word[i] == letter:
                    self.guessed_word[i] = letter
        else:
            self.attempts -= 1

    def print_guessed_word(self):
        print(" ".join(self.guessed_word))

    def game_over(self):
        if "_" not in self.guessed_word:
            return True
        elif self.attempts == 0:
            return True
        else:
            return False

def main():
    hangman = Hangman()
    while True:
        print(hangman.print_hangman())
        print("Attempts left: ", hangman.attempts)
        print("Guessed word: ", end="")
        hangman.print_guessed_word())
        guess = input("Enter your guess: ").lower()
        if len(guess) != 1:
            print("Invalid guess. Please enter a single letter.")
            continue
        if guess in hangman.guessed_letters:
            print("You already guessed this letter. Try again!")
            continue
        hangman.guessed_letters.append(guess)
        hangman.check_guess(guess)
        if hangman.game_over():
            break

    if "_" not in hangman.guessed_word:
        print("\n Congratulations! You won! The word was: ", hangman.word)
    else:
        print("\n Sorry, you ran out of attempts. The word was: ", hangman.word)

if __name__ == "__main__":
    main()