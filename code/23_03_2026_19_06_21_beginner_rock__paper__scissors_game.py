# Rock, Paper, Scissors Game
import random

def game():
    choices = ['rock', 'paper', 'scissors']
    computer_choice = random.choice(choices)

    user_choice = input('Enter rock, paper, or scissors: ').lower()

    while user_choice not in choices:
        user_choice = input('Invalid choice. Enter rock, paper, or scissors: ').lower()

    if user_choice == computer_choice:
        print(f'Both players selected {user_choice}. It\'s a tie!')
    elif (user_choice == 'rock' and computer_choice == 'scissors') or \
         (user_choice == 'paper' and computer_choice == 'rock') or \
         (user_choice == 'scissors' and computer_choice == 'paper'):
        print(f'{user_choice.capitalize()} beats {computer_choice}. You win!')
    else:
        print(f'{computer_choice.capitalize()} beats {user_choice}. Computer wins!')

if __name__ == '__main__':
    game()