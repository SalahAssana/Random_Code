# Guessing Game
# A simple program that asks for user input and responds based on a predefined dictionary.

# Dictionary to store the possible answers and their corresponding responses
answers = {
    "hello": "Hi! How are you?",
    "goodbye": "See you later!",
    "howareyou": "I'm doing well, thanks!",
}

def main():
    # Initialize game state
    while True:
        # Ask user for input
        user_input = input("Enter a message (or 'quit' to exit): ")
        
        # Check if the user wants to quit
        if user_input.lower() == "quit":
            print("Goodbye!")
            break
        
        # Try to find a matching answer in the dictionary
        if user_input.lower() in answers:
            print(answers[user_input.lower()])
        else:
            print("I didn't understand that. Try again!")

if __name__ == '__main__':
    main()