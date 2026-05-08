#include <stdio.h>
#include <stdlib.h>

// Define a struct to represent a student's grades
typedef struct {
    char name[20];
    int assignments;
    int quizzes;
    int exams;
} Student;

// Function to calculate the grade for each type of assessment
float calculate_grade(int score, int max_score) {
    return (float)score / max_score * 100.0f;
}

// Function to calculate the overall grade for a student
float calculate_overall_grade(Student* student) {
    float total = 0.0f;

    // Calculate the weighted average of assignments, quizzes, and exams
    total += calculate_grade(student->assignments, 100) * 0.3f;
    total += calculate_grade(student->quizzes, 50) * 0.2f;
    total += calculate_grade(student->exams, 200) * 0.5f;

    return total;
}

// Function to print the student's grades
void print_grades(Student* student) {
    printf("Student Name: %s\n", student->name);
    printf("Assignments: %.2f%%\n", calculate_grade(student->assignments, 100));
    printf("Quizzes: %.2f%%\n", calculate_grade(student->quizzes, 50));
    printf("Exams: %.2f%%\n", calculate_grade(student->exams, 200));
    printf("Overall Grade: %.2f%%\n", calculate_overall_grade(student));
}

int main() {
    // Create an array of students
    Student students[3] = {
        {"John Doe", 80, 40, 180},
        {"Jane Smith", 90, 50, 190},
        {"Bob Johnson", 70, 30, 170}
    };

    // Print each student's grades
    for (int i = 0; i < sizeof(students) / sizeof(Student); i++) {
        print_grades(&students[i]);
        printf("\n");
    }

    return 0;
}