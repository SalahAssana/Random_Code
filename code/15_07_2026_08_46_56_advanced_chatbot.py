import re
import numpy as np
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

class Chatbot:
    def __init__(self):
        self.intent_dict = {
            'greeting': ['hi', 'hello', 'hey'],
            'goodbye': ['bye', 'see you later', 'goodbye'],
            'help': ['help me', 'assist me', 'what can i do']
        }
        self.response_dict = {
            'greeting': "Hi! How can I help you?",
            'goodbye': "See you later!",
            'help': "I'm here to assist you. What's on your mind?"
        }

    def process_input(self, user_input):
        # Tokenize and lowercase the input
        tokens = re.split(r'\W+', user_input.lower())
        
        # Identify the intent
        for intent, keywords in self.intent_dict.items():
            if any(keyword in tokens for keyword in keywords):
                return intent

        return None

    def generate_response(self, intent):
        return self.response_dict.get(intent, "I'm not sure what you mean.")

    def respond(self, user_input):
        intent = self.process_input(user_input)
        response = self.generate_response(intent)
        
        print("Chatbot:", response)

def main():
    chatbot = Chatbot()
    
    while True:
        user_input = input("User: ")
        chatbot.respond(user_input)

if __name__ == '__main__':
    main()