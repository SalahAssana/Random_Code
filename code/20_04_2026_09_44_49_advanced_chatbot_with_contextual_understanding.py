import nltk
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
import numpy as np
import tflearn
import random
import json
import pickle

lemmatizer = WordNetLemmatizer()
json_data = open('intents.json').read()
intents = json.loads(json_data)

words = []
docs_x = []
classes = []
documents = []

for intent in intents['intents']:
    for pattern in intent['patterns']:
        wrds = nltk.word_tokenize(pattern)
        words.extend(wrds)
        documents.append((wrds, intent['tag']))
    if intent['tag'] not in classes:
        classes.append(intent['tag'])

words = [lemmatizer.lemmatize(w) for w in words if len(w) > 2]
words = sorted(list(set(words)))

max_words = len(words)
documents = np.array(documents)

# create training data
train_x = []
train_y = []

for document in documents:
    wrds = document[0]
    tag = document[1]
    bag = []
    wrd_counts = {}
    for word in wrds:
        if word not in wrd_counts:
            wrd_counts[word] = 1
        else:
            wrd_counts[word] += 1
    for word, count in wrd_counts.items():
        bag.append(count / max_words)
    train_x.append(bag)

    output_row = [0 for _ in range(len(classes))]
    output_row[classes.index(tag)] = 1
    train_y.append(output_row)

# create and train the model
model = tflearn.DNN(tflearn.input_data(shape=(None, max_words)), 
                     tensorboard_dir='tflearn_logs')

model.fit(train_x, train_y, n_epoch=1000, shuffle=True, show_metric=True)
model.save('chatbot_model.tflearn')

def clean_up_sentence(sentence):
    sentence_words = nltk.word_tokenize(sentence)
    sentence_words = [lemmatizer.lemmatize(word) for word in sentence_words]
    return sentence_words

def bag_of_words(sentence, words):
    sentence_words = clean_up_sentence(sentence)
    bag = np.zeros(len(words))
    for s in sentence_words:
        for i,w in enumerate(words):
            if w == s:
                bag[i] += 1
    return np.array(bag)

def predict_class(sentence, model):
    p = bag_of_words(sentence, words)
    res = model.predict(np.array([p]))[0]
    result_index = list(res).index(max(res))
    tag = classes[result_index]
    if tag:
        return tag

def get_response(intents_json, intents, tag):
    for intent in intents['intents']:
        if intent['tag'] == tag:
            return random.choice(intent['responses'])

def chatbot_response(sentence):
    bag = bag_of_words(sentence, words)
    res = model.predict(np.array([bag]))[0]
    result_index = list(res).index(max(res))
    tag = classes[result_index]

    if tag:
        for intent in intents['intents']:
            if intent['tag'] == tag:
                return get_response(intents_json, intents, tag)

if __name__ == '__main__':
    while True:
        sentence = input('You: ')
        chatbot_response(sentence)