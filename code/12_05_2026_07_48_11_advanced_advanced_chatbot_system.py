import nltk
from nltk.stem import WordNetLemmatizer
nltk.download('wordnet')
nltk.download('punkt')

import random
import pickle
import numpy
import tflearn
from tflearn.layers.core import input_data, dropout, flatten
from tflearn.layers.conv import conv_2d, max_pool_2d

lemmatizer = WordNetLemmatizer()

 intents = {
    "greeting": {"pattern":"hello|hi", "responses": ["Hello! How are you today?","Hi there! I'm happy to help."]},
    "goodbye": {"pattern":"goodbye|see you", "responses": ["Goodbye! It was nice chatting with you.", "See you later!"]}
}

def clean_up_sentence(sentence):
    sentence_words = nltk.word_tokenize(sentence)
    sentence_words = [lemmatizer.lemmatize(word) for word in sentence_words]
    return " ".join(sentence_words)

def bag_of_words(sentence, words):
    sentence_words = clean_up_sentence(sentence)
    bag = [0] * len(words)
    for s_word in sentence_words:
        for word, index in enumerate(words):
            if word == s_word:
                bag[index] += 1
    return numpy.array(bag)

def predict_class(sentence, model):
    p = bag_of_words(sentence, words)
    res = model.predict(numpy.array([p]))[0]
    ERROR_THRESHOLD = 0.25
    results = [[i,r] for i,r in enumerate(res) if r > ERROR_THRESHOLD]

    # sort by strength of probability
    results.sort(key=lambda x: x[1], reverse=True)

    return_list = []
    for r in results:
        return_list.append({"intent": intents["intents"][r[0]]['tag'], "probability": str(r[1])})

    return return_list

def getResponse(intents_list, intents_json):
    tag = intents_list[0]['intent']
    responses = []

    # check which intent was found
    for i in intents_json['intents']:
        if (i['tag'] == tag):
            # select a random response from the intents dictionary
            resp = random.choice(i['responses'])
            responses.append(resp)

    return random.choice(responses)

words = []
pickle_in = open("words.pickle","rb")
words = pickle.load(pickle_in)

model = tflearn.DNN(tflearn.input_data(shape=[1, len(words)]))
model.load("model.tflearn")

def chatbot_response(msg):
    ints = predict_class(msg, model)
    res = getResponse(ints, intents)
    return res

if __name__ == "__main__":
    while True:
        msg = input("")
        print(chatbot_response(msg))