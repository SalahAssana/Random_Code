#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for student records
typedef struct {
    char name[50];
    int grade;
} Student;

// Function to add a new student record
void addStudent(Student* students, int* size, char* name, int grade) {
    if (*size >= 10) { // Limit the number of students to 10
        printf("Grade book is full. Cannot add more students.\n");
        return;
    }

    strcpy(students[(*size)].name, name);
    students[(*size)].grade = grade;

    (*size)++;
}

// Function to update a student's grade
void updateStudent(Student* students, int size, char* name, int newGrade) {
    for (int i = 0; i < size; i++) {
        if (strcmp(students[i].name, name) == 0) {
            students[i].grade = newGrade;
            printf("Updated %s's grade to %d.\n", name, newGrade);
            return;
        }
    }

    printf("Student not found. Cannot update grade.\n");
}

// Function to remove a student record
void removeStudent(Student* students, int* size, char* name) {
    for (int i = 0; i < *size; i++) {
        if (strcmp(students[i].name, name) == 0) {
            for (int j = i + 1; j < *size; j++) {
                students[j - 1] = students[j];
            }
            (*size)--;

            printf("Removed %s from the grade book.\n", name);
            return;
        }
    }

    printf("Student not found. Cannot remove.\n");
}

// Function to print all student records
void printStudents(Student* students, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s: %d\n", students[i].name, students[i].grade);
    }
}

int main() {
    Student students[10];
    int size = 0;

    // Add some initial data
    addStudent(students, &size, "John Doe", 85);
    addStudent(students, &size, "Jane Smith", 92);
    addStudent(students, &size, "Bob Brown", 78);

    printf("Current student records:\n");
    printStudents(students, size);

    // Update a student's grade
    updateStudent(students, size, "John Doe", 90);

    printf("\nUpdated student records:\n");
    printStudents(students, size);

    // Remove a student record
    removeStudent(students, &size, "Bob Brown");

    printf("\nFinal student records:\n");
    printStudents(students, size);

    return 0;
}