# Import necessary libraries
import nltk
from nltk.tokenize import word_tokenize
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from transformers import pipeline
import pandas as pd
nltk.download('punkt')

class Chatbot:
    def __init__(self):
        self.intent_mapping = {
            'greet': ['hello', 'hi', 'hey'],
            'goodbye': ['bye', 'goodbye', 'see you'],
            'book_flight': ['book flight', 'reserve flight'],
            'cancel_flight': ['cancel flight', 'reschedule']
        }
        self.intent_recognizer = pipeline('text-classification')
        self.tfidf_vectorizer = TfidfVectorizer()
        
    def tokenize_text(self, text):
        return word_tokenize(text)
    
    def get_intent(self, tokens):
        tokenized_query = ' '.join(tokens)
        classification_result = self.intent_recognizer(tokenized_query)
        intent = max(classification_result, key=lambda x: x['score'])['label']
        return intent
    
    def respond(self, intent):
        if intent == 'greet':
            return 'Hello! How can I help you today?'
        elif intent == 'goodbye':
            return 'Goodbye! Have a great day!'
        elif intent == 'book_flight':
            return 'I\'d be happy to book your flight. Can you please provide me with more details about the flight you want to book?'
        elif intent == 'cancel_flight':
            return 'Sorry to hear that. I can help you cancel or reschedule your flight. Please let me know what you need.'
    
    def process_query(self, query):
        tokens = self.tokenize_text(query)
        intent = self.get_intent(tokens)
        response = self.respond(intent)
        return response

# Create a chatbot instance
chatbot = Chatbot()

if __name__ == '__main__':
    while True:
        user_input = input('You: ')
        print(f'Chatbot: {chatbot.process_query(user_input)}')