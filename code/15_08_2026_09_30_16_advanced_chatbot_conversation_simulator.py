import random
from collections import defaultdict
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
from nltk.corpus import stopwords

class Chatbot:
    def __init__(self):
        self.intent_map = {
            "greeting": ["hi", "hello", "hey"],
            "goodbye": ["bye", "see you later", "adios"],
            "help": ["how can i help", "what can i do for you", "need assistance"]
        }
        self.response_map = {
            "greeting": ["Hello! I'm happy to assist you.", "Hi there, what's on your mind?", "Hey, how are you doing today?"],
            "goodbye": ["Goodbye! It was nice chatting with you.", "See you later! Have a great day.", "Adios for now!"],
            "help": ["I'm here to help. What do you need assistance with?", "What's on your mind? I'll do my best to assist you.", "Need some advice? I'm all ears."]
        }
        self.intent = None
        self.response = None

    def process_input(self, input_text):
        lemmatizer = WordNetLemmatizer()
        stop_words = set(stopwords.words("english"))
        tokens = word_tokenize(input_text.lower())
        filtered_tokens = [lemmatizer.lemmatize(token) for token in tokens if token not in stop_words]
        intent = None
        for key, values in self.intent_map.items():
            if any(value in filtered_tokens for value in values):
                intent = key
                break
        return intent

    def generate_response(self, intent):
        responses = self.response_map.get(intent, [])
        if responses:
            response = random.choice(responses)
            return response
        else:
            return "Sorry, I didn't understand that."

    def simulate_conversation(self):
        while True:
            user_input = input("You: ")
            intent = self.process_input(user_input)
            response = self.generate_response(intent)
            print(f"Chatbot: {response}")
            if intent == "goodbye":
                break

if __name__ == '__main__':
    chatbot = Chatbot()
    chatbot.simulate_conversation()