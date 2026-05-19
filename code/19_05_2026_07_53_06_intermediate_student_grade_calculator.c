#include <stdio.h>
#include <stdlib.h>

// Define a structure to hold student information
typedef struct {
    char name[50];
    int assignments;
    double assignment1, assignment2, assignment3;
    int exams;
    double exam1, exam2, exam3;
} Student;

// Function to calculate the grade for a single student
double calculateGrade(Student* student) {
    // Calculate the weighted average of assignments
    double assignmentAverage = (student->assignment1 + student->assignment2 + student->assignment3) / 3.0;

    // Calculate the weighted average of exams
    double examAverage = (student->exam1 + student->exam2 + student->exam3) / 3.0;

    // Calculate the final grade as a weighted average of assignments and exams
    return (0.4 * assignmentAverage) + (0.6 * examAverage);
}

// Function to print the grade for a single student
void printGrade(Student* student, double grade) {
    printf("Student: %s\n", student->name);
    printf("Grade: %.2f\n", grade);
}

int main() {
    // Define students and their grades
    Student students[3] = {
        {"John Doe", 3, 90.0, 80.0, 70.0, 1, 85.0, 95.0, 92.0},
        {"Jane Smith", 3, 85.0, 75.0, 95.0, 2, 90.0, 88.0, 98.0},
        {"Bob Brown", 3, 95.0, 80.0, 90.0, 3, 85.0, 92.0, 95.0}
    };

    // Calculate and print the grade for each student
    for (int i = 0; i < 3; i++) {
        double grade = calculateGrade(&students[i]);
        printGrade(&students[i], grade);
    }

    return 0;
}