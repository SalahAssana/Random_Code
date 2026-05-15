#!/usr/bin/env python3
# encoding: utf-8

import random
import string

class Hangman:
    def __init__(self):
        self.word_list = ["apple", "banana", "cherry", "date", "elderberry"]
        self.selected_word = random.choice(self.word_list)
        self.guessed_letters = []
        self.attempts = 10

    def display_board(self):
        print("Attempts left: {}".format(self.attempts))
        word_display = ""
        for char in self.selected_word:
            if char in self.guessed_letters:
                word_display += char
            else:
                word_display += "_"
        print(word_display)

    def get_guessed_letter(self):
        while True:
            try:
                letter = input("Guess a letter: ").lower()
                if len(letter) != 1 or not letter.isalpha():
                    raise ValueError
                return letter
            except ValueError:
                print("Invalid input. Please enter a single alphabetic character.")

    def check_win(self):
        return set(self.selected_word) == set(self.guessed_letters)

    def play(self):
        while self.attempts > 0 and not self.check_win():
            self.display_board()
            letter = self.get_guessed_letter()
            if letter in self.selected_word:
                self.guessed_letters.append(letter)
            else:
                self.attempts -= 1
                print("Incorrect! The character is not in the word.")
        self.display_board()
        if self.check_win():
            print("Congratulations, you won!")
        else:
            print("Sorry, you lost. The correct word was: {}".format(self.selected_word))

if __name__ == '__main__':
    game = Hangman()
    game.play()