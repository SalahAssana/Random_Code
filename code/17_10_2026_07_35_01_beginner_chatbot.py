# Chatbot program in Python
# Complexity Level: BEGINNER

# Define a dictionary to store chatbot responses
chatbot_responses = {
    "hello": "Hello! How can I help you today?",
    "hi": "Hi! What's on your mind?",
    "what's your name": "My name is ChatBot, nice to meet you!",
    "exit": "Goodbye! It was nice chatting with you."
}

def chatbot():
    # Initialize user input and response
    user_input = ""
    while True:
        # Get user input
        user_input = input("You: ")
        
        # Check if the user wants to exit
        if user_input.lower() == "exit":
            print(chatbot_responses["exit"])
            break
        
        # Check chatbot responses and respond accordingly
        elif user_input.lower() in chatbot_responses:
            print(chatbot_responses[user_input.lower()])
        else:
            print("ChatBot: Sorry, I didn't understand that.")
    
    return

if __name__ == '__main__':
    chatbot()