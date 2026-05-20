# Student Grade Calculator
# INTERMEDIATE complexity project

import statistics as stats

class Student:
    def __init__(self, name):
        self.name = name
        self.assignments = []
        self.quizzes = []
        self.exams = []

    def add_grade(self, grade_type, grade_value):
        if grade_type == 'assignment':
            self.assignments.append(grade_value)
        elif grade_type == 'quiz':
            self.quizzes.append(grade_value)
        elif grade_type == 'exam':
            self.exams.append(grade_value)
        else:
            print("Invalid grade type. Please use 'assignment', 'quiz', or 'exam'.")

    def calculate_average(self, grade_type):
        if grade_type == 'assignment':
            return stats.mean(self.assignments)
        elif grade_type == 'quiz':
            return stats.mean(self.quizzes)
        elif grade_type == 'exam':
            return stats.mean(self.exams)
        else:
            print("Invalid grade type. Please use 'assignment', 'quiz', or 'exam'.")

def main():
    student = Student('John Doe')

    # Add grades
    student.add_grade('assignment', 85)
    student.add_grade('assignment', 90)
    student.add_grade('quiz', 95)
    student.add_grade('quiz', 92)
    student.add_grade('exam', 88)

    # Calculate and print averages
    print(f"Average Assignment Grade: {student.calculate_average('assignment'):.2f}")
    print(f"Average Quiz Grade: {student.calculate_average('quiz'):.2f}")
    print(f"Average Exam Grade: {student.calculate_average('exam'):.2f}")

if __name__ == '__main__':
    main()