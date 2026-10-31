# Student Grade Tracker
import sys

class Student:
    def __init__(self, name):
        self.name = name
        self.grades = []

    def add_grade(self, grade):
        self.grades.append(grade)

    def average_grade(self):
        return sum(self.grades) / len(self.grades)


def main():
    try:
        students = []
        while True:
            print("Menu:")
            print("1. Add student")
            print("2. Add grade for a student")
            print("3. Calculate and display grades for all students")
            print("4. Exit")
            choice = input("Choose an option: ")
            if choice == "1":
                name = input("Enter the student's name: ")
                students.append(Student(name))
            elif choice == "2":
                if not students:
                    print("No students added yet.")
                    continue
                name = input("Enter the student's name: ")
                for student in students:
                    if student.name == name:
                        grade = float(input("Enter the grade: "))
                        student.add_grade(grade)
                        break
                else:
                    print("Student not found.")
            elif choice == "3":
                if not students:
                    print("No students added yet.")
                    continue
                for student in students:
                    print(f"Name: {student.name}, Average Grade: {student.average_grade()}")
            elif choice == "4":
                sys.exit(0)
            else:
                print("Invalid option. Please choose a valid option.")

    except ValueError:
        print("Invalid input. Please enter a number.")
    except Exception as e:
        print(f"An error occurred: {str(e)}")


if __name__ == '__main__':
    main()