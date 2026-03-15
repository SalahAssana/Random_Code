import nltk
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
import pickle
import numpy as np

from keras.models import Sequential
from keras.layers import Dense, Activation, Dropout
from keras.optimizers import Adam

lemmatizer = WordNetLemmatizer()
model_path = 'chatbot_model.h5'
intents_json = 'intents.json'

class ChatBot:
    def __init__(self):
        self.model = None
        self.data = None

    def load_data(self, filename):
        with open(filename, 'rb') as f:
            return pickle.load(f)

    def create_model(self, data):
        model = Sequential()
        model.add(Dense(64, input_shape=(4000,), activation='relu'))
        model.add(Dropout(0.5))
        model.add(Dense(64, activation='relu'))
        model.add(Dropout(0.5))
        model.add(Dense(len(data), activation='softmax'))
        model.compile(optimizer=Adam(lr=0.001), loss='categorical_crossentropy', metrics=['accuracy'])
        return model

    def train_model(self):
        if self.model is None:
            self.data = self.load_data('data.pkl')
            self.model = self.create_model(self.data)
            self.model.fit(np.array([i[0] for i in self.data]), np.array([i[1] for i in self.data]), epochs=10)

    def predict(self, text):
        if self.model is None:
            self.train_model()
        text = word_tokenize(text.lower())
        text = [lemmatizer.lemmatize(word) for word in text]
        text = ' '.join(text)
        text = np.array([text])
        return self.model.predict(text)

    def get_response(self, text):
        intents = pickle.load(open(intents_json, 'rb'))
        responses = []
        for intent in intents:
            if intent['trigger'] == text:
                responses.extend(intent['responses'])
        return random.choice(responses)

if __name__ == '__main__':
    chatbot = ChatBot()
    while True:
        user_input = input('You: ')
        response = chatbot.get_response(user_input)
        print(f'ChatBot: {response}')