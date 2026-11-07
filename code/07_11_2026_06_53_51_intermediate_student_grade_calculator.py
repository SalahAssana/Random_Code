# Student Grade Calculator
import math

class Student:
    def __init__(self, name):
        self.name = name
        self.assignments = []
        self.quizzes = []

    def add_assignment(self, grade):
        self.assignments.append(grade)

    def add_quiz(self, grade):
        self.quizzes.append(grade)

    def calculate_average(self):
        assignment_avg = sum(self.assignments) / len(self.assignments)
        quiz_avg = sum(self.quizzes) / len(self.quizzes)
        return (assignment_avg + quiz_avg) / 2

def calculate_grade(student):
    average = student.calculate_average()
    if average < 60:
        return "F"
    elif average >= 60 and average < 70:
        return "D"
    elif average >= 70 and average < 80:
        return "C"
    elif average >= 80 and average < 90:
        return "B"
    else:
        return "A"

def main():
    students = [
        Student("Alice"),
        Student("Bob"),
        Student("Charlie")
    ]

    students[0].add_assignment(85)
    students[0].add_quiz(92)
    students[1].add_assignment(78)
    students[1].add_quiz(88)
    students[2].add_assignment(95)
    students[2].add_quiz(96)

    for student in students:
        grade = calculate_grade(student)
        print(f"{student.name}'s grade is {grade}")

if __name__ == '__main__':
    main()