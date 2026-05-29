# Chatbot with Natural Language Processing
import nltk
from nltk.tokenize import word_tokenize
from nltk.stem import PorterStemmer
from nltk.parse import ChartParser
from nltk.sem import ScopeForm

nltk.download('averaged_perceptron_tagger')
nltk.download('punkt')

class Chatbot:
    def __init__(self):
        self.parser = ChartParser()
        self.stemmer = PorterStemmer()

    def tokenize(self, text):
        return word_tokenize(text)

    def stem(self, word):
        return self.stemmer.stem(word.lower())

    def parse_sentence(self, sentence):
        tokens = self.tokenize(sentence)
        parse_tree = self.parser.parse(' '.join(map(str, tokens)))
        return parse_tree

    def answer_question(self, question):
        tokens = self.tokenize(question)
        stemmed_tokens = [self.stem(token) for token in tokens]
        scope_form = ScopeForm()
        for i, token in enumerate(stemmed_tokens):
            if token.endswith('ing'):
                scope_form.add_sentence((i-1, i+1), 'VBP')
            elif token.endswith('ed'):
                scope_form.add_sentence((i-1, i+1), 'VBD')
        return scope_form

    def respond(self, question):
        parse_tree = self.parse_sentence(question)
        answer = ''
        for leaf in parse_tree.leaves():
            if leaf[0].startswith('what') or leaf[0].startswith('who'):
                answer = f"I'm {self.answer_question(leaf[0]).get_answer()}."
            elif leaf[0].endswith('are'):
                answer = "Yes, they are."
            else:
                answer = f"I don't know about that. Can you rephrase?"
        return answer

if __name__ == '__main__':
    chatbot = Chatbot()
    print(chatbot.respond("What is the average temperature in New York?"))
    print(chatbot.respond("Who wrote the book 'To Kill a Mockingbird'?"))
    print(chatbot.respond("Are the Red Sox playing tonight?"))