import nltk
from nltk.tokenize import word_tokenize
from nltk.sentiment import SentimentIntensityAnalyzer
import random
import string
import re

class Chatbot:
    def __init__(self):
        self.sentiment = SentimentIntensityAnalyzer()
        self.knowledge_base = {
            'hello': ['Hi! How can I help you today?'],
            'hi': ['Hey, what\'s up?'],
            'how are you': ['I\'m doing well, thanks for asking. What about you?'],
            'goodbye': ['See you later!']
        }
    
    def respond(self, user_input):
        # Tokenize the input
        tokens = word_tokenize(user_input)
        
        # Check if the input is a greeting or goodbye
        if re.match(r'\b(hi|hello|hey)\b', ' '.join(tokens)):
            return random.choice(self.knowledge_base.get(''.join(tokens), []))
        
        # Perform sentiment analysis on the input
        sentiment_scores = self.sentiment.polarity_scores(user_input)
        
        # Determine the tone of the response based on the sentiment
        if sentiment_scores['compound'] > 0.5:
            return 'That sounds great! I\'m happy to help you with that.'
        elif sentiment_scores['compound'] < -0.5:
            return 'Sorry to hear that. Maybe we can brainstorm a solution together?'
        else:
            return 'I see. Let me think about it for a moment... Ah, yes! That reminds me of something. Maybe I can help you with that.'
    
    def train(self):
        # Load the knowledge base from a file or database
        pass

if __name__ == '__main__':
    chatbot = Chatbot()
    while True:
        user_input = input('You: ')
        response = chatbot.respond(user_input)
        print(f'Chatbot: {response}')