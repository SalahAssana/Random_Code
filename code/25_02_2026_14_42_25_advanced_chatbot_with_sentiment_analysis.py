import nltk
from nltk.sentiment import SentimentIntensityAnalyzer
import random
from collections import defaultdict

class Chatbot:
    def __init__(self):
        self.sentiments = defaultdict(int)
        self.responses = {
            'positive': ['I\'m glad you feel that way!', 'That\'s great to hear!'],
            'negative': ['Sorry to hear that.', 'That\'s disappointing.'],
            'neutral': ['That\'s interesting.', 'I\'ll keep that in mind.']
        }
        self.sia = SentimentIntensityAnalyzer()

    def analyze_sentiment(self, text):
        sentiment = self.sia.polarity_scores(text)
        if sentiment['compound'] > 0.05:
            return 'positive'
        elif sentiment['compound'] < -0.05:
            return 'negative'
        else:
            return 'neutral'

    def respond(self, text):
        sentiment = self.analyze_sentiment(text)
        response = random.choice(self.responses[sentiment])
        return response

    def chat(self):
        while True:
            user_input = input('You: ')
            if user_input.lower() == 'quit':
                break
            print(f'Chatbot: {self.respond(user_input)}')

if __name__ == '__main__':
    chatbot = Chatbot()
    chatbot.chat()