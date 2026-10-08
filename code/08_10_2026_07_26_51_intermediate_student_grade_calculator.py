# Student Grade Calculator
# A multi-concept program that calculates student grades based on assignments and exams

class Student:
    def __init__(self, name):
        self.name = name
        self.assignments = []
        self.exams = []

    def add_assignment(self, grade, weight):
        self.assignments.append((grade, weight))

    def add_exam(self, grade, weight):
        self.exams.append((grade, weight))

    def calculate_grade(self):
        total_weight = sum(weight for _, weight in self.assignments + self.exams)
        assignment_score = sum(grade * weight / total_weight for grade, weight in self.assignments)
        exam_score = sum(grade * weight / total_weight for grade, weight in self.exams)
        return (assignment_score + exam_score) / 2


def main():
    students = []

    while True:
        print("1. Add Student")
        print("2. Calculate Grades")
        print("3. Exit")

        choice = input("Choose an option: ")

        if choice == "1":
            name = input("Enter student's name: ")
            students.append(Student(name))
            print(f"Student '{name}' added.")
        elif choice == "2":
            for i, student in enumerate(students):
                print(f"\nGrades for {student.name}:")
                total_weight = sum(weight for _, weight in student.assignments + student.exams)
                assignment_score = sum(grade * weight / total_weight for grade, weight in student.assignments)
                exam_score = sum(grade * weight / total_weight for grade, weight in student.exams)
                print(f"Assignment: {assignment_score:.2f} (average)")
                print(f"Exam: {exam_score:.2f} (average)")
                print(f"Overall Grade: {(assignment_score + exam_score) / 2:.2f}\n")
        elif choice == "3":
            break
        else:
            print("Invalid option. Please choose again.")

    if __name__ == '__main__':
        main()