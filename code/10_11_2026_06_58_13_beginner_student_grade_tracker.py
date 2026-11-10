# Student Grade Tracker
# BEGINNER complexity project

students = {
    "John": {"math": 90, "science": 85, "english": 95},
    "Jane": {"math": 95, "science": 80, "english": 90},
    "Bob": {"math": 85, "science": 75, "english": 88}
}

def calculate_average(students):
    total = 0
    count = 0
    for student in students.values():
        for subject in student:
            total += student[subject]
        count += len(student)
    return total / (count * 3)

if __name__ == '__main__':
    average = calculate_average(students)
    print("Average grade:", average)