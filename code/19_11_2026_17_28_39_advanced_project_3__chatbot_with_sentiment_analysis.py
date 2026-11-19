import nltk
from nltk.sentiment import SentimentIntensityAnalyzer
from nltk.tokenize import word_tokenize
import random
import string
from collections import defaultdict

class Chatbot:
    def __init__(self):
        self.sia = SentimentIntensityAnalyzer()
        self.intent_map = {
            'greeting': ['hello', 'hi', 'hey'],
            'goodbye': ['goodbye', 'see you later', 'cya'],
            'complaint': ['bad', 'terrible', 'awful']
        }
        self.response_map = {
            'greeting': ['Hello! What can I help you with today?', 'Hi there! How are you doing?'],
            'goodbye': ['Goodbye! Have a great day!', 'See you later! Take care!'],
            'complaint': ['Sorry to hear that. Can you tell me more about what\'s bothering you?', 'That sounds frustrating. I\'m here to listen and help if I can.']
        }

    def analyze_sentiment(self, text):
        sentiment = self.sia.polarity_scores(text)
        return {'positive': sentiment['pos'], 'negative': sentiment['neg']}

    def intent_detection(self, text):
        words = word_tokenize(text.lower())
        intents = []
        for k, v in self.intent_map.items():
            if any(word in words for word in v):
                intents.append(k)
        return intents

    def respond(self, intent):
        if intent in self.response_map:
            return random.choice(self.response_map[intent])
        else:
            return 'I didn\'t quite catch that. Can you try again?'

    def chat(self):
        print('Welcome to our chatbot! What\'s on your mind today?')
        while True:
            user_input = input('> ')
            sentiment = self.analyze_sentiment(user_input)
            intent = self.intent_detection(user_input)[0]
            response = self.respond(intent)
            print(response)
            if 'goodbye' in intent:
                break
        print('Thank you for chatting with us!')

if __name__ == '__main__':
    chatbot = Chatbot()
    chatbot.chat()