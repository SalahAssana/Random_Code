# Student Grade Calculator
import statistics

class Student:
    def __init__(self, name):
        self.name = name
        self.assignments = []
        self.quizzes = []
        self.exams = []

    def add_assignment(self, grade):
        self.assignments.append(grade)

    def add_quiz(self, grade):
        self.quizzes.append(grade)

    def add_exam(self, grade):
        self.exams.append(grade)

    def calculate_gpa(self):
        assignments_avg = statistics.mean(self.assignments)
        quizzes_avg = statistics.mean(self.quizzes)
        exams_avg = statistics.mean(self.exams)
        return (assignments_avg + quizzes_avg + exams_avg) / 3

def main():
    student1 = Student("John")
    student2 = Student("Jane")

    # Add grades
    student1.add_assignment(85)
    student1.add_assignment(90)
    student1.add_quiz(70)
    student1.add_exam(95)

    student2.add_assignment(80)
    student2.add_assignment(75)
    student2.add_quiz(60)
    student2.add_exam(90)

    # Calculate GPAs
    print(f"{student1.name}'s GPA: {student1.calculate_gpa():.2f}")
    print(f"{student2.name}'s GPA: {student2.calculate_gpa():.2f}")

if __name__ == '__main__':
    main()