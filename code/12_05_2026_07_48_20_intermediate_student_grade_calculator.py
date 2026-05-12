# Student Grade Calculator

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

    def get_grade_average(self):
        assignment_avg = self.calculate_average(self.assignments)
        quiz_avg = self.calculate_average(self.quizzes)
        exam_avg = self.calculate_average(self.exams)
        return f"{self.name}'s grade averages: Assignments - {assignment_avg}, Quizzes - {quiz_avg}, Exams - {exam_avg}"

def main():
    student1 = Student("John")
    student2 = Student("Jane")

    student1.add_grade('assignment', 90)
    student1.add_grade('assignment', 85)
    student1.add_grade('quiz', 95)
    student1.add_grade('exam', 98)

    student2.add_grade('assignment', 80)
    student2.add_grade('assignment', 92)
    student2.add_grade('quiz', 88)
    student2.add_grade('exam', 96)

    print(student1.get_grade_average())
    print(student2.get_grade_average())

if __name__ == '__main__':
    main()