# Hangman Game

import random

HANGMAN_PICS = ['''
  +---+
  |   |
      |
      |
      |
      |
=========''', '''
  +---+
  |   |
  O   |
      |
      |
      |
=========''', '''
  +---+
  |   |
  O   |
  |   |
      |
      |
=========''', '''
  +---+
  |   |
  O   |
 /|   |
      |
      |
=========''', '''
  +---+
  |   |
  O   |
 /|\  |
      |
      |
=========''', '''
  +---+
  |   |
  O   |
 /|\  |
 /    |
      |
=========''', '''
  +---+
  |   |
  O   |
 /|\  |
 / \  |
      |
=========''']

words = ['apple', 'banana', 'cherry', 'date', 'elderberry', 'fig', 'grape', 'honeydew']

def get_random_word():
    return random.choice(words)

def draw_hangman(missed_letters, correct_guesses):
    print(HANGMAN_PICS[6-missed_letters])

def get_guess(already_guessed):
    while True:
        guess = input('Guess a letter: ').lower()
        if len(guess) != 1:
            print('Please enter a single letter.')
        elif guess in already_guessed:
            print('You have already guessed that letter. Try again.')
        elif guess not in 'abcdefghijklmnopqrstuvwxyz':
            print('Please enter a letter from the alphabet.')
        else:
            return guess

def play_hangman():
    word = get_random_word()
    missed_letters = 0
    correct_guesses = ''
    print('Let\'s play Hangman!')
    while True:
        draw_hangman(missed_letters, correct_guesses)
        guess = get_guess(correct_guesses)
        if guess in word:
            correct_guesses += guess
            word_list = list(word)
            display = ''
            for letter in word_list:
                if letter in correct_guesses:
                    display += letter + ' '
                else:
                    display += '_ '
            print(display)
            if '_' not in display:
                print('Congratulations! You guessed the word!')
                return
        else:
            missed_letters += 1
            if missed_letters == 6:
                draw_hangman(missed_letters, correct_guesses)
                print(f'Sorry, you didn\'t guess the word. It was {word}.')
                return

if __name__ == '__main__':
    play_hangman()