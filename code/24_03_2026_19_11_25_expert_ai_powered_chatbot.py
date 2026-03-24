#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import re
import numpy as np
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from transformers import pipeline

class ChatBot:
    def __init__(self):
        self.intent_recognizer = pipeline("intent", model="ibeltas/sentiment-intent")
        self.sentiment_analyzer = pipeline("sentiment_analysis")
        self.response_generator = pipeline("text-generation")

    def process_input(self, user_input):
        intent_result = self.intent_recognizer(user_input)
        sentiment_result = self.sentiment_analyzer(user_input)[0]
        return {"intent": intent_result[0]["intent"], "sentiment": sentiment_result["label"]}

    def generate_response(self, user_input, context=None):
        if context is None:
            context = ""
        intent = self.process_input(user_input)["intent"]
        sentiment = self.process_input(user_input)["sentiment"]

        if re.match(r"\b(what|how|when)\b", user_input, re.IGNORECASE):
            return "I'm still learning. Can you please help me improve my responses?"
        elif re.match(r"\b(love|hate|like|dislike)\b", user_input, re.IGNORECASE):
            if sentiment == "POSITIVE":
                return f"I love it too! {random.choice(['That\'s awesome!', 'I completely agree!'])}"
            else:
                return f"Sorry to hear that. Can you tell me more about what's bothering you?"
        elif intent == "greeting":
            return f"Hello there! I'm happy to chat with you. How are you doing today?"
        elif intent == "goodbye":
            return f"It was nice chatting with you. Have a great day!"
        else:
            try:
                response = self.response_generator(
                    prompt=user_input,
                    context=context,
                    max_length=200,
                    temperature=0.7
                )[0]["generated_text"]
                return response
            except Exception as e:
                print(f"Error generating response: {e}")
                return "Sorry, I didn't quite understand that. Can you please rephrase your question?"

    def run(self):
        while True:
            user_input = input("You: ")
            if re.match(r"\b(quit|exit)\b", user_input, re.IGNORECASE):
                print("Goodbye!")
                break
            response = self.generate_response(user_input)
            print(f"ChatBot: {response}")

if __name__ == "__main__":
    chatbot = ChatBot()
    chatbot.run()