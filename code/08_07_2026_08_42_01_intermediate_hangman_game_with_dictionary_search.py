# Hangman Game with Dictionary Search

import random

class Word:
    def __init__(self, word):
        self.word = word
        self.guessed = ["_"] * len(word)

    def reveal(self):
        return "".join(self.guessed)


class Hangman:
    def __init__(self, dictionary_file):
        self.dictionary = self.load_dictionary(dictionary_file)
        self.word = random.choice(list(self.dictionary.keys()))
        self.guessed_letters = []
        self.missed_letters = []

    def load_dictionary(self, file_name):
        with open(file_name, "r") as f:
            return {line.strip(): 0 for line in f}

    def is_word_guessed(self):
        return all(letter != "_" for letter in self.word.guessed)

    def has_missed_letters(self):
        return len(self.missed_letters) >= 6

    def guess_letter(self, letter):
        if letter in self.word:
            for i, char in enumerate(self.word.word):
                if char == letter:
                    self.word.guessed[i] = letter
        else:
            self.missed_letters.append(letter)

    def play(self):
        while True:
            print("Hangman Word: " + self.word.reveal())
            guess = input("Guess a letter or type 'quit' to stop playing: ")
            if guess.lower() == "quit":
                break
            elif len(guess) != 1:
                print("Please guess one letter at a time.")
            else:
                self.guess_letter(guess)
            if self.is_word_guessed():
                print("Congratulations, you guessed the word!")
                break
            elif self.has_missed_letters():
                print("Game Over! You missed too many letters.")
                break

    def run(self):
        self.play()


if __name__ == '__main__':
    game = Hangman("dictionary.txt")
    game.run()