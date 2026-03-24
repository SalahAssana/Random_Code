# Student Grade Calculator
import random

class Student:
    def __init__(self, name):
        self.name = name
        self.assignments = []
        self.quizzes = []
        self.exams = []

    def add_grade(self, type, grade):
        if type == 'assignment':
            self.assignments.append(grade)
        elif type == 'quiz':
            self.quizzes.append(grade)
        elif type == 'exam':
            self.exams.append(grade)

    def calculate_average(self, grades):
        return sum(grades) / len(grades)

def calculate_final_grade(student):
    assignments = student.calculate_average(student.assignments)
    quizzes = student.calculate_average(student.quizzes)
    exams = student.calculate_average(student.exams)
    
    if assignments >= 85 and quizzes >= 90 and exams >= 95:
        return 'A'
    elif assignments >= 75 and quizzes >= 80 and exams >= 90:
        return 'B'
    elif assignments >= 70 and quizzes >= 80 and exams >= 85:
        return 'C'
    else:
        return 'F'

def main():
    students = []
    
    for _ in range(5):
        name = f'Student {random.randint(1, 100)}'
        student = Student(name)
        assignments = [random.randint(0, 100) for _ in range(3)]
        quizzes = [random.randint(0, 100) for _ in range(2)]
        exams = [random.randint(0, 100)]
        
        for i, grade in enumerate(assignments):
            student.add_grade('assignment', grade)
        for i, grade in enumerate(quizzes):
            student.add_grade('quiz', grade)
        for i, grade in enumerate(exams):
            student.add_grade('exam', grade)
        
        students.append(student)

    for student in students:
        print(f'\n{student.name}\'s grades:')
        print(f'Assignments: {", ".join(map(str, student.assignments))}')
        print(f'Quizzes: {", ".join(map(str, student.quizzes))}')
        print(f'Exams: {", ".join(map(str, student.exams))}')
        
        final_grade = calculate_final_grade(student)
        print(f'\nFinal Grade: {final_grade}\n')

if __name__ == '__main__':
    main()