# Simple Chatbot
# Beginner-friendly chatbot that responds to basic user queries

# List of possible user inputs (queries)
user_inputs = ["hello", "hi", "how are you", "what's up", "quit"]

# Dictionary mapping user inputs to responses
responses = {
    "hello": "Hello! I'm a simple chatbot.",
    "hi": "Hi! How can I help you?",
    "how are you": "I'm just an AI, so I don't have feelings like humans do. But I'm here to help with any questions!",
    "what's up": "Not much! Just waiting for your next question.",
    "quit": "Goodbye! It was nice chatting with you."
}

# Main function
def chatbot():
    print("Welcome to the simple chatbot!")
    
    # Loop until user quits
    while True:
        # Get user input (query)
        user_input = input("You: ")
        
        # Check if user wants to quit
        if user_input.lower() in ["quit", "goodbye"]:
            print(responses["quit"])
            break
        
        # Provide response based on user query
        elif user_input.lower() in user_inputs:
            print(responses[user_input.lower()])
        else:
            print("Sorry, I didn't understand that. Try again!")

if __name__ == '__main__':
    chatbot()