# Student Grade Calculator

def calculate_grade(score):
    # Define the grade ranges and corresponding labels
    grade_ranges = [(80, 'A'), (70, 79, 'B'), (60, 69, 'C'), (50, 59, 'D'), (0, 49, 'F')]
    
    for low, high, label in grade_ranges:
        if score >= high:
            return label
    return ''

def main():
    # Define the student's scores
    scores = [90, 80, 70, 60, 50]

    # Calculate and display each student's grade
    for score in scores:
        grade = calculate_grade(score)
        print(f"Student's score: {score}, Grade: {grade}")

if __name__ == '__main__':
    main()