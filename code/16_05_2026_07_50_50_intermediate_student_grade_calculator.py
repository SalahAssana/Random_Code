# Student Grade Calculator
import random

class Student:
    def __init__(self, name):
        self.name = name
        self.assignments = []
        self.projects = []

    def add_assignment(self, grade):
        self.assignments.append(grade)

    def add_project(self, grade):
        self.projects.append(grade)

    def calculate_grade(self):
        total_assignments = sum(self.assignments)
        total_projects = sum(self.projects)
        return (total_assignments + 0.3 * total_projects) / len(self.assignments + self.projects)


def generate_student_data(num_students):
    students = []
    for _ in range(num_students):
        name = f"Student {random.randint(1, 100)}"
        student = Student(name)
        num_assignments = random.randint(2, 5)
        num_projects = random.randint(1, 3)
        assignments = [random.uniform(0.0, 1.0) for _ in range(num_assignments)]
        projects = [random.uniform(0.0, 1.0) for _ in range(num_projects)]
        student.add_assignment(*assignments)
        student.add_project(*projects)
        students.append(student)
    return students


def print_student_grades(students):
    for student in students:
        grade = student.calculate_grade()
        print(f"{student.name}: {grade:.2f}")


if __name__ == '__main__':
    num_students = 5
    students = generate_student_data(num_students)
    print_student_grades(students)