# Hangman Game

import random

word_list = ['apple', 'banana', 'cherry', 'date', 'elderberry']
chosen_word = random.choice(word_list)

display = ['_'] * len(chosen_word)
print(' '.join(display))

guessed_letters = []
tries = 10

while tries > 0:
    guess = input('Guess a letter: ').lower()
    
    if len(guess) != 1:
        print('Please, guess only one letter.')
        continue
    
    if guess in guessed_letters:
        print('You already guessed this letter. Try another one.')
        continue
    guessed_letters.append(guess)
    
    if guess not in chosen_word:
        tries -= 1
        print(f"Incorrect! You have {tries} remaining tries.")
    else:
        print(f"Correct! The word contains '{guess}'.")
        
    display = [letter if letter.lower() == guess else '_' for letter in chosen_word]
    print(' '.join(display))
    
    if '_' not in display:
        print('Congratulations, you guessed the word!')
        break
else:
    print(f"Game over. The word was {chosen_word}.")