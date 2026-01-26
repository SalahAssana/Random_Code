# Simple Chatbot in Python

import re

# List of possible responses from chatbot
responses = {
    "hello": ["Hello! How are you?", "Hi there! What can I help you with?"],
    "hi": ["Hey! How's it going?", "Hi! What's up?"],
    "help": ["What do you need help with?", "I'd be happy to assist you. What's your question?"],
    "quit": ["Goodbye!", "See you next time!"]
}

# Regular expression pattern for matching user input
pattern = re.compile(r"^[a-zA-Z\s]+$")

def chatbot():
    print("Welcome to the Simple Chatbot!")
    
    while True:
        # Get user input
        user_input = input("You: ")
        
        # Check if the user wants to quit
        if user_input.lower() == "quit":
            break
        
        # Match user input with possible responses
        for response in responses.get(user_input.lower(), []):
            print(f"Chatbot: {response}")
        
        # If no match, respond with a generic message
        if not pattern.match(user_input):
            print("Chatbot: Sorry, I didn't understand that. Try rephrasing.")

if __name__ == '__main__':
    chatbot()