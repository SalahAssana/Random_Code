import random

class Hangman:
    def __init__(self):
        self.word_list = ["apple", "banana", "cherry", "date", "elderberry"]
        self.word = random.choice(self.word_list)
        self.guessed_letters = []
        self.hints = ["fruit", "sweet", "red", "yellow", "black"]

    def get_word_status(self):
        word_status = ""
        for char in self.word:
            if char in self.guessed_letters:
                word_status += char
            else:
                word_status += "-"
        return word_status

    def check_guess(self, letter):
        if letter in self.word:
            self.guessed_letters.append(letter)
            if all(char in self.guessed_letters for char in self.word):
                print(f"Congratulations! You guessed the word: {self.word}")
                return False
        else:
            print("Oops, that letter is not in the word!")
        return True

    def give_hint(self):
        hint = random.choice(self.hints)
        print(f"Hint: The word is a {hint}.")
        return self.check_guess(input("Guess a letter: "))

    def play_game(self):
        while True:
            print(self.get_word_status())
            if not self.give_hint():
                break

if __name__ == '__main__':
    game = Hangman()
    game.play_game()