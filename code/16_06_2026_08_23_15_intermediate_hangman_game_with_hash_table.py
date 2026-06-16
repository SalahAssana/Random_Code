# Hangman Game with Hash Table

import random

class Word:
    def __init__(self):
        self.word = "programming"
        self.guessed = ["_"] * len(self.word)
        self.frequencies = {"P": 2, "R": 2, "O": 1, "G": 1, "A": 3, "M": 1, "I": 1}

    def display_word(self):
        return " ".join(self.guessed)

    def check_guess(self, letter):
        for i in range(len(self.word)):
            if self.word[i] == letter:
                self.guessed[i] = letter

class Game:
    def __init__(self):
        self.word = Word()
        self.guesses = 0
        self.won = False

    def play(self):
        while not self.won and self.guesses < 6:
            print("\n" + self.word.display_word())
            guess = input("Guess a letter: ").upper()
            if self.word.frequencies.get(guess) is None:
                print("Invalid guess. Try again.")
                self.guesses += 1
            else:
                self.word.check_guess(guess)
                if "_" not in self.word.guessed:
                    self.won = True
        if self.won:
            print("\nCongratulations! You won!")
        else:
            print("\nGame over. The word was " + self.word.word)

if __name__ == '__main__':
    game = Game()
    game.play()