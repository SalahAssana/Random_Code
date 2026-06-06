import random

# Define the possible answers
answers = ["It's certain", "It's likely", "It's possible", "It's unlikely", "It's not happening"]

def get_user_question():
    # Ask for user input (question)
    question = input("Ask your question, and I'll give you a random answer: ")
    return question

def generate_random_answer():
    # Generate a random index for the answers list
    random_index = random.randint(0, len(answers) - 1)
    return answers[random_index]

def main():
    print("Welcome to the Guessing Game!")
    
    while True:
        user_question = get_user_question()
        answer = generate_random_answer()
        print(f"{user_question}: {answer}")
        
        # Ask if the user wants to play again
        response = input("Do you want to ask another question? (y/n) ")
        if response.lower() != 'y':
            break

if __name__ == '__main__':
    main()