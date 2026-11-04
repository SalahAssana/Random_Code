# Chatbot Response Generator
# BEGINNER project

# Importing necessary libraries
import random

# Predefined answers for chatbot responses
answers = {
    "hello": ["Hello!", "Hi! How can I help you?", "Hey there!"],
    "goodbye": ["Goodbye!", "See you later!", "Bye for now!"],
    "thanks": ["You're welcome!", "No problem at all.", "Anytime, feel free to ask."],
    default: ["I didn't quite catch that. Can you rephrase?", "That's a good question. Let me think about it...", "Hmm, I'm not sure what you mean by that."]
}

# Chatbot response generator function
def generate_response(user_input):
    user_input = user_input.lower()  # Convert to lowercase for easier matching

    if user_input in answers:
        return random.choice(answers[user_input])  # Return a random answer from the predefined list
    else:
        return "I didn't understand that. Can you rephrase?"

# Main program starts here
if __name__ == '__main__':
    while True:  # Loop until program is interrupted or exited manually
        user_input = input("You: ")