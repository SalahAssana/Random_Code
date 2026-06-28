# Rock, Paper, Scissors game

# Initialize wins and losses to 0
wins = 0
losses = 0

while True:
    # Ask user for their choice
    user_choice = input("Enter your choice (rock/paper/scissors) or 'q' to quit: ").lower()

    # Check if user wants to quit
    if user_choice == 'q':
        break

    # Generate computer's random choice
    import random
    computer_choice = random.choice(['rock', 'paper', 'scissors'])

    print(f"Computer chose {computer_choice}.")

    # Determine winner
    if user_choice == computer_choice:
        result = "It's a tie!"
    elif (user_choice == 'rock' and computer_choice == 'scissors') or \
         (user_choice == 'paper' and computer_choice == 'rock') or \
         (user_choice == 'scissors' and computer_choice == 'paper'):
        result = "You win this round!"
        wins += 1
    else:
        result = "Computer wins this round."
        losses += 1

    print(result)

    # Print final score
    print(f"Score: You - {wins}, Computer - {losses}\n")

if __name__ == '__main__':
    pass