import re
from collections import defaultdict
from enum import Enum

class State(Enum):
    START = 1
    GREETING = 2
    QUESTION = 3
    RESPONSE = 4
    GOODBYE = 5

class Chatbot:
    def __init__(self):
        self.state = State.START
        self.intent_map = defaultdict(list)
        self.intent_map[State.GREETING.name].append(re.compile(r'hello|hi'))
        self.intent_map[State.QUESTION.name].append(re.compile(r'what.*|how.*'))
        self.intent_map[State.RESPONSE.name].append(re.compile(r'thank.*|thankyou'))

    def process_input(self, input_text):
        if self.state == State.START:
            for regex in self.intent_map[State.GREETING.name]:
                if regex.match(input_text):
                    return self.greeting_response()
        elif self.state == State.GREETING:
            for regex in self.intent_map[State.QUESTION.name]:
                if regex.match(input_text):
                    return self.question_response()
        elif self.state == State.QUESTION:
            for regex in self.intent_map[State.RESPONSE.name]:
                if regex.match(input_text):
                    return self.response_response()
        elif self.state == State.RESPONSE:
            if input_text.lower() == 'goodbye':
                return self.goodbye_response()
        return None

    def greeting_response(self):
        print("Hello! I'm happy to help you.")
        self.state = State.QUESTION
        return "What's on your mind?"

    def question_response(self):
        print("I'm all ears!")
        self.state = State.RESPONSE
        return "How can I assist you today?"

    def response_response(self):
        print("You're welcome! What else is on your mind?")
        self.state = State.QUESTION

    def goodbye_response(self):
        print("Goodbye, it was nice chatting with you!")
        self.state = State.START

if __name__ == '__main__':
    chatbot = Chatbot()
    while True:
        user_input = input('You: ')
        response = chatbot.process_input(user_input)
        if response is not None:
            print(f'Chatbot: {response}')