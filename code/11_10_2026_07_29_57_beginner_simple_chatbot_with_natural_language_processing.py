# Import necessary libraries
import nltk
from nltk.tokenize import word_tokenize
from nltk.sentiment.vader import SentimentIntensityAnalyzer
import random

# Initialize sentiment analyzer
sia = SentimentIntensityAnalyzer()

# Define a dictionary to store responses based on user input
responses = {
    "hello": ["Hi! How are you today?", "Hello! What's on your mind?"],
    "how are you": ["I'm doing great, thanks for asking!", "I'm good, but I'm learning all the time."],
    "what is your sentiment": ["It's neutral, but it can change based on user input.", "It depends on what the user says!"],
    "quit": ["Goodbye, thanks for chatting with me!"]
}

# Define a function to respond to user input
def respond(user_input):
    # Tokenize the user input into words
    tokens = word_tokenize(user_input.lower())
    
    # Check if the user said something nice or mean
    sentiment = sia.polarity_scores(user_input)
    if sentiment["compound"] > 0.5:
        response_key = "positive"
    elif sentiment["compound"] < -0.5:
        response_key = "negative"
    else:
        response_key = random.choice(["neutral", "random"])
    
    # Choose a response based on the user's input and sentiment
    if tokens[0] in responses:
        return random.choice(responses[tokens[0]])
    elif response_key == "positive":
        return random.choice(["That's great to hear!", "I'm glad you're happy."])
    elif response_key == "negative":
        return random.choice(["Sorry to hear that.", "I hope things get better."])
    else:
        return random.choice(responses["random"])

# Main program
if __name__ == '__main__':
    print("Welcome to our simple chatbot! Type 'quit' to exit.")
    
    while True:
        user_input = input("You: ")
        
        if user_input.lower() == "quit":
            break
        
        response = respond(user_input)
        print(f"Chatbot: {response}")