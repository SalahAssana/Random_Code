# Chatbot Conversation Simulator

import random
from collections import defaultdict

class Chatbot:
    def __init__(self):
        self.conversation_history = []
        self.responses = {
            "hello": ["hi", "hey", "hello"],
            "goodbye": ["see you later", "goodbye", "cya"],
            "help": ["I can help with that", "what do you need?", "ask me anything"],
            "default": ["sorry, I didn't understand", "can you rephrase?"]
        }
        self.intent_to_response = {
            "greeting": {"hello": random.choice(self.responses["hello"]),
                         "goodbye": random.choice(self.responses["goodbye"])},
            "request": {"help": random.choice(self.responses["help"])}
        }

    def process_input(self, input_text):
        if not input_text:
            return self.responses["default"][0]
        intent = self.determine_intent(input_text)
        if intent:
            response = self.intent_to_response.get(intent).get(input_text.lower(), "")
            if response:
                return response
        return self.responses["default"][0]

    def determine_intent(self, input_text):
        for intent in self.intent_to_response:
            if any(word in input_text.lower() for word in self.intent_to_response[intent]):
                return intent
        return "default"

def main():
    chatbot = Chatbot()
    while True:
        user_input = input("You: ")
        response = chatbot.process_input(user_input)
        print(f"Chatbot: {response}")
        if user_input.lower() == "quit":
            break

if __name__ == '__main__':
    main()