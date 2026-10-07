# Hangman Game
import random

class Hangman:
    def __init__(self):
        self.difficulty_levels = ['easy', 'medium', 'hard']
        self.word_list = ['apple', 'banana', 'cherry', 'date', 'elderberry']
        self.word = ''
        self.guessed_letters = []
        self.rounds = 0
        self.max_rounds = 6

    def get_word(self, difficulty):
        if difficulty == 'easy':
            return random.choice(['apple', 'banana', 'date'])
        elif difficulty == 'medium':
            return random.choice(['cherry', 'elderberry', 'fig'])
        else:
            return random.choice(['grape', 'honeydew', 'jackfruit'])

    def play_round(self):
        self.word = self.get_word(random.choice(self.difficulty_levels))
        guessed_letters = []
        for letter in self.word:
            if letter not in guessed_letters:
                print('_ ', end='')
            else:
                print(letter, end=' ')
        print()

    def check_guess(self, guess):
        if len(guess) != 1 or not guess.isalpha():
            return False
        if guess.lower() in self.guessed_letters:
            return False
        self.guessed_letters.append(guess)
        for letter in self.word:
            if letter == guess.lower():
                return True
        return False

    def game_over(self):
        print('Game Over!')
        print(f'Word was: {self.word}')
        return len(self.guessed_letters) / len(self.word) >= 0.7

if __name__ == '__main__':
    game = Hangman()
    while True:
        difficulty = input("Choose a difficulty level (easy, medium, hard): ")
        if difficulty not in game.difficulty_levels:
            print('Invalid choice. Try again.')
            continue
        game.play_round()
        for _ in range(game.max_rounds):
            guess = input('Guess a letter: ')
            if game.check_guess(guess):
                print('Good guess!')
            else:
                print(f'Sorry, {guess} is not in the word.')
            if game.game_over():
                break
        else:
            print('Congratulations! You won!')