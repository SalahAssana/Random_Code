# Import necessary libraries
import nltk
from nltk.tokenize import word_tokenize
import random
import numpy as np
from collections import defaultdict

# Define a class for the chatbot's personality
class Personality:
    def __init__(self):
        self.mood = "happy"
        self.intensity = 50

    def change_mood(self, new_mood):
        self.mood = new_mood

    def get_mood(self):
        return self.mood

    def change_intensity(self, new_intensity):
        self.intensity = new_intensity

    def get_intensity(self):
        return self.intensity


# Define a class for the chatbot's knowledge base
class KnowledgeBase:
    def __init__(self):
        self.sentences = []

    def add_sentence(self, sentence):
        self.sentences.append(sentence)

    def get_sentences(self):
        return self.sentences

    def generate_response(self, query):
        responses = []
        for sentence in self.sentences:
            if query.lower() in sentence.lower():
                responses.append(sentence)
        return random.choice(responses)


# Define a class for the chatbot's AI logic
class AiLogic:
    def __init__(self, personality, knowledge_base):
        self.personality = personality
        self.knowledge_base = knowledge_base

    def process_query(self, query):
        if self.personality.get_mood() == "sad":
            response = "I'm feeling down today..."
        elif self.personality.get_intensity() > 75:
            response = "WOOHOO! Let's party!"
        else:
            response = self.knowledge_base.generate_response(query)
        return response


# Define the chatbot's main function
def main():
    # Initialize the personality and knowledge base
    personality = Personality()
    knowledge_base = KnowledgeBase()

    # Add some initial sentences to the knowledge base
    knowledge_base.add_sentence("Hello, how are you today?")
    knowledge_base.add_sentence("I'm doing great, thanks for asking!")
    knowledge_base.add_sentence("What's your favorite hobby?")

    # Initialize the AI logic with the personality and knowledge base
    ai_logic = AiLogic(personality, knowledge_base)

    # Start a conversation loop
    while True:
        query = input("You: ")
        response = ai_logic.process_query(query)
        print(f"Chatbot: {response}")


# Run the chatbot's main function if this script is run directly
if __name__ == '__main__':
    main()