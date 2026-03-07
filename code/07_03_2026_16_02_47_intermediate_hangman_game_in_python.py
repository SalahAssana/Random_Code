# hangman.py

import random
import string

class Hangman:
    def __init__(self):
        self.word = self.generate_word()
        self.guessed = ['_'] * len(self.word)
        self.attempts = 6

    def generate_word(self):
        words = ["apple", "banana", "cherry", "date", "elderberry"]
        return random.choice(words)

    def guess(self, letter):
        if letter in string.ascii_lowercase:
            for i in range(len(self.word)):
                if self.word[i] == letter:
                    self.guessed[i] = letter
        else:
            print("Invalid input. Please enter a single lowercase letter.")

    def check_win(self):
        return '_' not in self.guessed

    def check_loss(self):
        return self.attempts <= 0

    def play(self):
        while True:
            print(' '.join(self.guessed))
            guess = input("Enter your guess: ")
            self.guess(guess)
            if self.check_win():
                print('Congratulations! You won!')
                break
            elif self.check_loss():
                print(f"Game over. The word was {self.word}.")
                break
            else:
                self.attempts -= 1
                print(f"You have {self.attempts} attempts left.")

    def __str__(self):
        return f"Word: {' '.join(self.guessed)}"

if __name__ == '__main__':
    game = Hangman()
    game.play()