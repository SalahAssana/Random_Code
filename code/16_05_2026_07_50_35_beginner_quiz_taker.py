# Quiz Taker
# Author: [Your Name]

class QuizTaker:
    def __init__(self):
        self.scores = {}

    def add_question(self, question, correct_answer):
        self.scores[question] = {"correct": 0, "incorrect": 0}

    def take_quiz(self):
        for question, answers in self.scores.items():
            answer = input(f"Question: {question} (type 'c' for correct or 'i' for incorrect): ")
            if answer.lower() == 'c':
                self.scores[question]["correct"] += 1
            elif answer.lower() == 'i':
                self.scores[question]["incorrect"] += 1

    def display_scores(self):
        print("Quiz Results:")
        for question, answers in self.scores.items():
            correct = answers["correct"]
            incorrect = answers["incorrect"]
            print(f"Question: {question}, Correct: {correct}, Incorrect: {incorrect}")

if __name__ == '__main__':
    quiz_taker = QuizTaker()
    quiz_taker.add_question("What is the capital of France?", "Paris")
    quiz_taker.add_question("Who is the CEO of SpaceX?", "Elon Musk")
    quiz_taker.take_quiz()
    quiz_taker.display_scores()