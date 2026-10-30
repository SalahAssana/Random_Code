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

def get_random_word():
    return random.choice(words)

def draw_hangman(missed_letters):
    print(HANGMAN_PICS[6-missed_letters])

def get_word_to_guess():
    word = get_random_word()
    guessed = ['_'] * len(word)
    return word, guessed

def play_game():
    word, guessed = get_word_to_guess()
    missed_letters = 0
    while True:
        print(' '.join(guessed))
        guess = input("Guess a letter or type 'quit' to stop: ").lower()
        if guess == 'quit':
            break
        elif len(guess) != 1:
            print("Please guess one letter at a time.")
        else:
            for i in range(len(word)):
                if word[i] == guess:
                    guessed[i] = guess
            if '_' not in guessed:
                print('Congratulations! You guessed the word.')
                break
            elif guess not in word:
                missed_letters += 1
                draw_hangman(missed_letters)
    if missed_letters == 6:
        print("Sorry, you didn't guess the word. The word was " + word)

if __name__ == '__main__':
    play_game()