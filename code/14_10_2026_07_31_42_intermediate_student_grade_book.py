# Student Grade Book Program

# Import necessary modules
import os

class StudentGradeBook:
    def __init__(self):
        self.grades = {}

    # Add student and grade to the book
    def add_student(self, student_name, grade):
        if student_name in self.grades:
            print("Student already exists. Please update existing grade.")
        else:
            self.grades[student_name] = grade

    # Remove student from the book
    def remove_student(self, student_name):
        if student_name in self.grades:
            del self.grades[student_name]
        else:
            print("Student not found.")

    # View all students and their grades
    def view_students(self):
        for student, grade in self.grades.items():
            print(f"{student}: {grade}")

    # Save the grades to a file
    def save_grades(self, filename="grades.txt"):
        with open(filename, "w") as f:
            for student, grade in self.grades.items():
                f.write(f"{student}:{grade}\n")

    # Load the grades from a file
    def load_grades(self, filename="grades.txt"):
        try:
            with open(filename, "r") as f:
                for line in f:
                    student, grade = line.strip().split(":")
                    self.grades[student] = int(grade)
        except FileNotFoundError:
            pass

# Main execution
if __name__ == "__main__":
    grade_book = StudentGradeBook()

    # Load existing grades (if any)
    grade_book.load_grades()

    while True:
        print("\n1. Add student and grade")
        print("2. Remove student")
        print("3. View all students and grades")
        print("4. Save grades to file")
        print("5. Quit")

        choice = input("Choose an option: ")

        if choice == "1":
            student_name = input("Enter student name: ")
            grade = int(input("Enter grade: "))
            grade_book.add_student(student_name, grade)
        elif choice == "2":
            student_name = input("Enter student name: ")
            grade_book.remove_student(student_name)
        elif choice == "3":
            grade_book.view_students()
        elif choice == "4":
            filename = input("Enter file name (default is 'grades.txt'): ") or "grades.txt"
            grade_book.save_grades(filename)
        elif choice == "5":
            break
        else:
            print("Invalid option. Please choose again.")