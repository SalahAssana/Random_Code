# Student Grade Tracker
# BEGINNER Complexity Level

grades = {
    "Alice": {"math": 90, "science": 85},
    "Bob": {"math": 95, "science": 92},
    "Charlie": {"math": 78, "science": 88}
}

def calculate_average(students):
    total_score = 0
    for student in students:
        total_score += sum(grades[student].values())
    return total_score / (len(grades) * 2)

if __name__ == '__main__':
    print("Student Grade Tracker")
    print("---------------------")

    average_math = calculate_average([student for student in grades if "math" in grades[student]])
    average_science = calculate_average([student for student in grades if "science" in grades[student]])

    print(f"Average Math Score: {average_math:.2f}")
    print(f"Average Science Score: {average_science:.2f}")