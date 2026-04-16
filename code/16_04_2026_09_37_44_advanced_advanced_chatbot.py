import nltk
from nltk.stem import WordNetLemmatizer
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation, Dropout
nltk.download('wordnet')

lemmatizer = WordNetLemmatizer()

class Chatbot:
    def __init__(self):
        self.model = None

    def train(self):
        # Load the dataset (synthetic data for this example)
        dataset = tf.data.Dataset.from_tensor_slices((['hi', 'hello', 'how are you', 'what\'s up'], ['hey', 'hi', 'I am good', 'not much']))
        dataset = dataset.batch(32)

        # Create a sequential model
        self.model = Sequential()
        self.model.add(Dense(64, activation='relu', input_shape=(1,)))
        self.model.add(Dropout(0.2))
        self.model.add(Dense(64, activation='relu'))
        self.model.add(Dropout(0.2))
        self.model.add(Dense(len(dataset), activation='softmax'))

        # Compile the model
        self.model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

        # Train the model
        self.model.fit(dataset, epochs=10)

    def respond(self, user_input):
        # Preprocess the input
        inputs = lemmatizer.lemmatize(user_input.lower())

        # Make predictions
        predictions = self.model.predict(inputs)

        # Get the highest probability index
        best_index = tf.argmax(predictions).numpy()

        # Return the corresponding response
        return best_index

if __name__ == '__main__':
    chatbot = Chatbot()
    chatbot.train()

    while True:
        user_input = input("User: ")
        response = chatbot.respond(user_input)
        print(f"Chatbot: {response}")