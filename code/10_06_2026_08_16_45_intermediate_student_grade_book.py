# Student Grade Book

class Student:
    def __init__(self, name):
        self.name = name
        self.grades = {}

    def add_grade(self, course, grade):
        if course in self.grades:
            self.grades[course] += [grade]
        else:
            self.grades[course] = [grade]

    def calculate_average(self):
        total = 0
        for grades in self.grades.values():
            total += sum(grades) / len(grades)
        return total

    def identify_areas_for_improvement(self):
        average_grades = {}
        for course, grades in self.grades.items():
            avg_grade = sum(grades) / len(grades)
            if avg_grade < 3.0:
                average_grades[course] = avg_grade
        return average_grades

def main():
    students = {"Alice": Student("Alice"), "Bob": Student("Bob")}
    
    while True:
        print("\n1. Add grade for a student")
        print("2. Calculate and display average grades for all students")
        print("3. Identify areas for improvement (courses with average grade < 3)")
        print("4. Exit program")

        choice = input("Enter your choice: ")

        if choice == "1":
            name = input("Enter the student's name: ")
            course = input("Enter the course name: ")
            grade = float(input("Enter the grade (0-5): "))
            students[name].add_grade(course, grade)
        elif choice == "2":
            for name, student in students.items():
                print(f"Average grades for {name}: {student.calculate_average()}")
        elif choice == "3":
            for name, student in students.items():
                areas_for_improvement = student.identify_areas_for_improvement()
                if areas_for_improvement:
                    print(f"{name} needs improvement in: {', '.join(areas_for_improvement)}")
        elif choice == "4":
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == '__main__':
    main()