import numpy as np
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
import random

class ChatbotConversationSimulator:
    def __init__(self):
        self.users = ["Alice", "Bob"]
        self.conversation_history = []
        self.vectorizer = TfidfVectorizer(min_df=1, max_features=1000)
        self.user_profiles = {}

    def get_user_input(self, user):
        print(f"{user}: ")
        input_text = input()
        return input_text

    def process_user_input(self, user_input, user):
        tokenized_text = word_tokenize(user_input.lower())
        lemmatizer = WordNetLemmatizer()
        lemmatized_text = [lemmatizer.lemmatize(word) for word in tokenized_text]
        return " ".join(lemmatized_text)

    def compute_similarity(self, user_profile, conversation_history):
        vectorized_conversation = self.vectorizer.fit_transform(conversation_history)
        vectorized_user_input = self.vectorizer.transform([user_profile])
        similarity_scores = cosine_similarity(vectorized_conversation, vectorized_user_input).flatten()
        return similarity_scores

    def update_user_profile(self, user_profile, conversation_history):
        if user_profile not in self.user_profiles:
            self.user_profiles[user_profile] = []
        self.user_profiles[user_profile].extend(conversation_history)

    def get_response(self, user_input, user):
        processed_input = self.process_user_input(user_input, user)
        if len(self.conversation_history) == 0:
            return f"Hello, {user}! I'm glad to chat with you."
        similarity_scores = self.compute_similarity(processed_input, self.conversation_history)
        most_similar_conversation = np.argmax(similarity_scores)
        response = self.conversation_history[most_similar_conversation]
        return response

    def simulate_conversation(self):
        while True:
            user_input = self.get_user_input(random.choice(self.users))
            response = self.get_response(user_input, random.choice(self.users))
            print(response)
            self.conversation_history.append(user_input)

if __name__ == '__main__':
    simulator = ChatbotConversationSimulator()
    simulator.simulate_conversation()