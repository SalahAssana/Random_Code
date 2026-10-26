# Importing necessary libraries
import random
import re

class ChatBot:
    def __init__(self):
        self.conversation_flow = {
            "greeting": {"response": "Hello! I'm happy to help you."},
            "hello": {"response": "Hi there! How are you today?"},
            "goodbye": {"response": "It was nice chatting with you. See you soon!"}
        }
        self.intent_mapping = {
            "greet": "greeting",
            "help": "info",
            "quit": "goodbye"
        }

    def get_response(self, user_input):
        user_input = re.sub(r'\W+', '', user_input).lower()
        for intent in self.intent_mapping:
            if intent in user_input:
                return self.conversation_flow[self.intent_mapping[intent]]["response"]
        return random.choice(["I didn't understand that.", "Sorry, I'm still learning."])

    def start_conversation(self):
        print("Welcome to the chatbot!")
        while True:
            user_input = input("> ")
            if user_input.lower() in ["goodbye", "quit"]:
                print(self.conversation_flow["goodbye"]["response"])
                break
            else:
                print(self.get_response(user_input))

if __name__ == '__main__':
    bot = ChatBot()
    bot.start_conversation()