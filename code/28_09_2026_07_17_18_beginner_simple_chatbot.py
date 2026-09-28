# Simple Chatbot in Python
import random

# Define chatbot responses
chatbot_responses = {
    "hello": ["Hello! How are you today?", "Hi! What's up?"],
    "goodbye": ["Goodbye! See you later!", "Bye for now!"],
    "thanks": ["You're welcome! Anytime!", "No problem at all!"]
}

# Define user input
user_input = input("Enter your message (type 'hello', 'goodbye' or 'thanks'): ")

# Check if the user input matches a chatbot response
if user_input.lower() in chatbot_responses:
    # Select a random response from the matching responses
    print(random.choice(chatbot_responses[user_input.lower()]))
else:
    # If no match, just respond with a generic message
    print("I didn't quite understand that. Try again!")

# Run the chatbot if this script is run directly (not imported)
if __name__ == '__main__':
    user_input = input("Enter your message (type 'hello', 'goodbye' or 'thanks'): ")
    if user_input.lower() in chatbot_responses:
        print(random.choice(chatbot_responses[user_input.lower()]))
    else:
        print("I didn't quite understand that. Try again!")