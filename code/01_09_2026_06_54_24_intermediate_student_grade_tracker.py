# Student Grade Tracker
# Author: <Your Name>

class Course:
    def __init__(self, name):
        self.name = name
        self.grades = []

    def add_grade(self, grade):
        self.grades.append(grade)

    def calculate_gpa(self):
        return sum(self.grades) / len(self.grades)


class Student:
    def __init__(self, name):
        self.name = name
        self.courses = {}

    def add_course(self, course_name, grades):
        if course_name not in self.courses:
            self.courses[course_name] = Course(course_name)
        for grade in grades:
            self.courses[course_name].add_grade(grade)

    def calculate_overall_gpa(self):
        total_points = 0
        credits = 0
        for _, course in self.courses.items():
            credits += 1
            total_points += len(course.grades) * 4.0  # assume each grade is worth 4 points
        return total_points / credits


def main():
    student = Student("John Doe")
    student.add_course("Math", [95, 92, 98])
    student.add_course("Science", [88, 90, 85])
    print(f"{student.name}'s Math GPA: {student.courses['Math'].calculate_gpa():.2f}")
    print(f"{student.name}'s Science GPA: {student.courses['Science'].calculate_gpa():.2f}")
    print(f"{student.name}'s Overall GPA: {student.calculate_overall_gpa():.2f}")


if __name__ == '__main__':
    main()