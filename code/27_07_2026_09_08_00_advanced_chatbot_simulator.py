import random
from collections import defaultdict
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from sklearn.naive_bayes import MultinomialNB

class Chatbot:
    def __init__(self):
        self.conversations = defaultdict(list)
        self.stop_words = set(stopwords.words('english'))
        self.lemmatizer = WordNetLemmatizer()
        self.vectorizer = TfidfVectorizer(min_df=0, max_features=5000)

    def train(self, conversations):
        for conversation in conversations:
            for message in conversation:
                tokens = word_tokenize(message)
                lemmatized_tokens = [self.lemmatizer.lemmatize(token) for token in tokens if token not in self.stop_words]
                vector = self.vectorizer.fit_transform([' '.join(lemmatized_tokens)])
                self.conversations[vector].append(message)

    def respond(self, message):
        vector = self.vectorizer.transform([message])
        scores = cosine_similarity(vector, [vec for vec in self.conversations.keys()])
        best_match = max(enumerate(scores), key=lambda x: (x[1], random.random()))[0]
        response = random.choice(self.conversations[list(self.conversations.keys())[best_match]].copy())
        return response

    def chat(self):
        print("Welcome to the chatbot!")
        while True:
            user_input = input("> ")
            if not user_input:
                break
            response = self.respond(user_input)
            print(response)

if __name__ == '__main__':
    conversations = [
        ["Hello", "How are you?", "I'm fine, thank you."],
        ["What's your name?", "I don't have a name.", "That's okay, I won't know either."],
        # Add more conversations here
    ]
    chatbot = Chatbot()
    chatbot.train(conversations)
    chatbot.chat()