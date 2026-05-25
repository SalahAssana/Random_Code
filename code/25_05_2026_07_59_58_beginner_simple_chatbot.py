# Simple Chatbot
# BEGINNER complexity project

def chatbot():
    print("Hello! I'm your simple chatbot.")
    while True:
        user_input = input("What's on your mind? ")
        
        if user_input.lower() == "hello":
            print("Hi there!")
        elif user_input.lower() == "goodbye":
            print("See you later!")
        elif user_input.lower() == "help":
            print("I can understand basic commands like 'hello', 'goodbye', and 'help'.")
        else:
            print("Sorry, I didn't quite get that. Try again!")

if __name__ == '__main__':
    chatbot()