# Hangman Game
import random

word_list = ['apple', 'banana', 'cherry', 'date', 'elderberry']
chosen_word = random.choice(word_list)

display = []
for letter in chosen_word:
    display.append('_')

guesses = 10
print(f"Let's play hangman! You have {guesses} guesses.")
print(' '.join(display))

while True:
    guess = input("Guess a letter: ").lower()
    
    if len(guess) != 1:
        print("Please, enter one character at a time.")
    elif guess not in 'abcdefghijklmnopqrstuvwxyz':
        print("Please, enter a valid English letter.")
    else:
        for i in range(len(chosen_word)):
            if chosen_word[i] == guess:
                display[i] = guess
        print(' '.join(display))
        
        if '_' not in display:
            print(f"Congratulations! You've guessed the word: {chosen_word}.")
            break
            
        if guesses > 1:
            guesses -= 1
            print(f"You have {guesses} remaining guesses.")
        else:
            print("Game over. The word was: " + chosen_word)
            break