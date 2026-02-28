# Student Grade Calculator
# A simple program to calculate and display student grades based on assignments and quizzes.

# Import necessary modules
import math

# Define constants for grade calculation
ASSIGNMENT_WEIGHTAGE = 0.6
QUIZ_WEIGHTAGE = 0.4

# Function to calculate total marks
def calculate_total_marks(assignment_marks, quiz_marks):
    return assignment_marks + quiz_marks

# Function to calculate final grade
def calculate_final_grade(total_marks):
    if total_marks < 40:
        return "F"
    elif total_marks < 50:
        return "D"
    elif total_marks < 60:
        return "C"
    elif total_marks < 70:
        return "B"
    else:
        return "A"

# Main program
if __name__ == '__main__':
    
    # Ask user for assignment and quiz marks
    assignment_marks = float(input("Enter the student's assignment marks (out of 100): "))
    quiz_marks = float(input("Enter the student's quiz marks (out of 100): "))

    # Calculate total marks
    total_marks = calculate_total_marks(assignment_marks, quiz_marks)

    # Calculate final grade
    final_grade = calculate_final_grade(total_marks)

    # Display the results
    print("Total Marks:", round(total_marks))
    print("Final Grade:", final_grade)