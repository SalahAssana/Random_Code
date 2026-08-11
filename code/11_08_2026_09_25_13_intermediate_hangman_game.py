# Hangman Game

import random

class Hangman:
    def __init__(self):
        self.word = self.load_word()
        self.guessed = ["_"] * len(self.word)
        self.misses = 0
        self.max_misses = 6

    def load_word(self):
        # Load word from file or generate a random one
        words = ['apple', 'banana', 'cherry', 'date', 'elderberry']
        return random.choice(words)

    def guess(self, letter):
        if letter in self.word:
            for i in range(len(self.word)):
                if self.word[i] == letter:
                    self.guessed[i] = letter
        else:
            self.misses += 1

    def is_won(self):
        return "_" not in self.guessed

    def is_lost(self):
        return self.misses >= self.max_misses

    def play(self):
        print("Welcome to Hangman!")
        while True:
            if self.is_won():
                print("Congratulations, you won! The word was: " + "".join(self.guessed))
                break
            elif self.is_lost():
                print("Game over! You didn't guess the word. It was: " + self.word)
                break
            else:
                print(" ".join(self.guessed))
                guess = input("Guess a letter: ")
                self.guess(guess)

if __name__ == '__main__':
    game = Hangman()
    game.play()