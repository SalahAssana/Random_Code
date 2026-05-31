import re
from collections import defaultdict

class Chatbot:
    def __init__(self):
        self.intent_patterns = {
            'greeting': r'\bhello\b|\bhi\b|\bhola\b',
            'farewell': r'\bgoodbye\b|\bcya\b',
            'thankyou': r'\bthanks\b|\btia\b',
            'query': r'\bwhat\b\s+(.*)\b|\bwant\b'
        }
        self.intent_responses = {
            'greeting': ['Hi! How can I help you today?', 'Hello there, what do you need?'],
            'farewell': ['Goodbye! Have a great day!', 'See you later!'],
            'thankyou': ['You\'re welcome!', 'No problem at all.'],
            'query': lambda x: f'You want {x}?'
        }
        self.intent_responses['query'] = defaultdict(lambda: 'I didn\'t understand that.')

    def process_input(self, user_input):
        for intent, pattern in self.intent_patterns.items():
            if re.search(pattern, user_input, re.IGNORECASE):
                return self.intent_responses[intent][0] if len(self.intent_responses[intent]) > 1 else self.intent_responses[intent][0].format(user_input)

    def run_chatbot(self):
        while True:
            user_input = input('You: ')
            print(f'Chatbot: {self.process_input(user_input)}')

if __name__ == '__main__':
    chatbot = Chatbot()
    chatbot.run_chatbot()