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

WORDS = ['apple', 'banana', 'cherry', 'date', 'elderberry', 'fig', 'grape', 'honeydew']

def get_word():
    return random.choice(WORDS)

def draw_hangman(attempts):
    print(HANGMAN_PICS[6-attempts])

def check_guess(word, guess):
    if len(guess) != 1:
        return False
    for letter in word:
        if letter == guess:
            return True
    return False

def play_game():
    word = get_word()
    guessed_word = ['_'] * len(word)
    attempts = 6
    
    while attempts > 0:
        print(' '.join(guessed_word))
        draw_hangman(attempts)
        guess = input('Guess a letter: ').lower()
        
        if check_guess(word, guess):
            for i in range(len(word)):
                if word[i] == guess:
                    guessed_word[i] = guess
        else:
            attempts -= 1
        
        if '_' not in guessed_word:
            print(' '.join(guessed_word))
            print('Congratulations! You won!')
            return
        
    print(' '.join(guessed_word))
    print('Game over. The word was ' + word + '.')
    return

if __name__ == '__main__':
    play_game()