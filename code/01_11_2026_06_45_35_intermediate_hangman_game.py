# Hangman Game
import random

class Hangman:
    def __init__(self):
        self.word = random.choice(["apple", "banana", "cherry", "date", "elderberry"])
        self.guessed_letters = []
        self.missed_guesses = 0
        self.game_over = False

    def display_word(self):
        word_display = ""
        for letter in self.word:
            if letter in self.guessed_letters:
                word_display += letter + " "
            else:
                word_display += "_ "
        return word_display.strip()

    def check_guess(self, guess):
        if len(guess) != 1:
            print("Please guess a single letter.")
            return False
        if guess not in self.word and guess not in self.guessed_letters:
            self.missed_guesses += 1
        else:
            self.guessed_letters.append(guess)
        return True

    def check_win(self):
        return set(self.word) == set(self.guessed_letters)

    def play(self):
        while not self.game_over:
            print(self.display_word())
            guess = input("Guess a letter: ")
            if not self.check_guess(guess):
                continue
            if self.check_win():
                print(f"Congratulations! You guessed the word {self.word}.")
                self.game_over = True
            elif self.missed_guesses >= 6:
                print(f"Game over. The word was {self.word}.")
                self.game_over = True

    def __str__(self):
        return f"Hangman Game: {' '.join(self.display_word().split())}\nMissed Guesses: {self.missed_guesses}"

if __name__ == '__main__':
    game = Hangman()
    print(game)