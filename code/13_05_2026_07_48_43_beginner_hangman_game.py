# Hangman Game in Python

import random

word_list = ['apple', 'banana', 'cherry', 'date', 'elderberry']

def game():
    word = random.choice(word_list)
    guessed_word = ['_'] * len(word)
    guessed_letters = []
    tries = 6
    
    print("Welcome to Hangman!")
    
    while tries > 0 and '_' in guessed_word:
        print(' '.join(guessed_word))
        guess = input("Guess a letter: ").lower()
        
        if len(guess) != 1:
            print("Please enter a single letter.")
            continue
        
        if guess in guessed_letters:
            print("You already guessed that letter. Try again!")
            continue
        
        guessed_letters.append(guess)
        
        if guess not in word:
            tries -= 1
            print(f"Incorrect! You have {tries} tries left.")
        else:
            for i in range(len(word)):
                if word[i] == guess:
                    guessed_word[i] = guess
                    
    if '_' not in guessed_word:
        print('Congratulations, you won!')
    else:
        print(f"Sorry, you didn't guess the word. The word was {word}.")
        
if __name__ == '__main__':
    game()