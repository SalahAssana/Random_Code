# Hangman Game with Dictionary Search
import random
import string

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

def getRandomWord(wordlist):
    # Return random index from wordlist
    return random.choice(wordlist)

def displayBoard(HANGMAN_PICS, missedLetters, correctLetters, secretWord):
    print(HANGMAN_PICS[len(missedLetters)])
    print()

    print('Missed letters:', end=' ')
    for letter in missedLetters:
        print(letter, end=' ')
    print()

    blanks = '_' * len(secretWord)

    # replace blanks with correctly guessed letters
    for i in range(len(secretWord)): 
        if secretWord[i] in correctLetters: 
            blanks = blankets[:i] + secretWord[i] + blanks[i+1:]

    for letter in blanks: 
        print(letter, end=' ')
    print()

def getGuess(alreadyGuessed):
    # Returns the letter the player entered
    return input('Guess a letter.').lower()

def playAgain():
    # This function returns True if the player wants to play again, otherwise it returns False.
    print('Do you want to play again? (yes or no)')
    return input().lower().startswith('y')

def main():
    wordlist = 'apple banana orange grapes kiwi strawberry'.split()
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

    missedLetters = ''
    correctLetters = ''
    secretWord = getRandomWord(wordlist)
    gameIsDone = False

    print('H A N G M A N')
    print(HANGMAN_PICS[0])
    print()

    while True:
        displayBoard(HANGMAN_PICS, missedLetters, correctLetters, secretWord)

        # Let the player type in a letter.
        guess = getGuess(missedLetters + correctLetters)

        if guess in secretWord:
            correctLetters += guess

            # Check if the guessed word is correct
            if '_' not in blanks:
                print('Congratulations! You won!')
                gameIsDone = True
        else:
            missedLetters += guess

            # check if player has made 7 mistakes.
            if len(missedLetters) == 6:
                displayBoard(HANGMAN_PICS, missedLetters, correctLetters, secretWord)
                print('Game Over! The word was ' + secretWord)
                gameIsDone = True

        if gameIsDone:
            if playAgain():
                main()
            else:
                print('Thanks for playing!')

if __name__ == '__main__':
    main()