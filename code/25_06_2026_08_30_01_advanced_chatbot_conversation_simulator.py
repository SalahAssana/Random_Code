import random
from collections import defaultdict
from datetime import datetime

class Chatbot:
    def __init__(self):
        self.conversation_history = []
        self.response_map = self.generate_response_map()

    def generate_response_map(self):
        response_map = defaultdict(list)
        responses = ["I'm not sure what you're saying.", "Can you please rephrase that?", "That's an interesting point."]
        topics = ["weather", "movies", "books"]
        for topic in topics:
            for _ in range(3):
                response_map[topic].append({"response": random.choice(responses), "next_topic": random.choice(topics)})
        return response_map

    def get_response(self, user_input, current_topic):
        if current_topic not in self.response_map:
            return "I'm not sure what to say about that."
        for response in self.response_map[current_topic]:
            if response["response"] == user_input:
                next_topic = random.choice(response["next_topic"])
                self.conversation_history.append((datetime.now(), user_input, current_topic))
                self.conversation_history.append((datetime.now(), response["response"], next_topic))
                return (response["response"], next_topic)
        return ("I'm not sure what you're saying.", "general")

    def display_conversation_history(self):
        for timestamp, input_text, topic in self.conversation_history:
            print(f"{timestamp}: {input_text} ({topic})")

def main():
    chatbot = Chatbot()
    while True:
        user_input = input("You: ")
        current_topic = "general"
        response, next_topic = chatbot.get_response(user_input, current_topic)
        print(f"Chatbot: {response}")
        if next_topic != "general":
            current_topic = next_topic
        if not user_input.lower().startswith("quit"):
            continue
        break

    print("\nConversation History:")
    chatbot.display_conversation_history()

if __name__ == '__main__':
    main()