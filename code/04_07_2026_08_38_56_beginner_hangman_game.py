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

words = ['apple', 'banana', 'cherry', 'date', 'elderberry']
word = random.choice(words)

display = []
for char in word:
    display.append('_')

guesses = ''
tries = 6

print('Welcome to Hangman!')
print(HANGMAN_PICS[0])
print(' '.join(display))
print(f'You have {tries} tries remaining.')

while True:
    guess = input('Guess a letter: ').lower()
    if len(guess) != 1:
        print('Please, enter one character.')
        continue
    if guess in guesses:
        print('You already guessed this letter. Try again.')
        continue
    guesses += guess

    found = False
    for i in range(len(word)):
        if word[i] == guess:
            display[i] = guess
            found = True

    if not found:
        tries -= 1
        print(HANGMAN_PICS[6 - tries])

    if '_' not in display:
        print('Congratulations! You guessed the word.')
        break
    elif tries == 0:
        print(f'Game over. The word was {word}.')
        break

    print(' '.join(display))
    print(f'You have {tries} tries remaining.')