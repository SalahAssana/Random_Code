#include <iostream>
#include <string>

using namespace std;

// Structure to represent a student's grade
struct Student {
    string name;
    double grade;
};

// Function to add a new student to the gradebook
void addStudent(Student students[], int& size, string name) {
    if (size >= 10) {
        cout << "Gradebook is full. Cannot add more students." << endl;
        return;
    }
    
    Student newStudent = {"", 0};
    newStudent.name = name;
    students[size] = newStudent;
    size++;
}

// Function to view all student grades
void viewGrades(Student students[], int size) {
    if (size == 0) {
        cout << "No students in the gradebook." << endl;
        return;
    }
    
    for (int i = 0; i < size; i++) {
        cout << "Student: " << students[i].name << ", Grade: " << students[i].grade << endl;
    }
}

// Function to remove a student from the gradebook
void removeStudent(Student students[], int& size, string name) {
    for (int i = 0; i < size; i++) {
        if (students[i].name == name) {
            for (int j = i + 1; j < size; j++) {
                students[j - 1] = students[j];
            }
            size--;
            cout << "Student removed from the gradebook." << endl;
            return;
        }
    }
    
    cout << "Student not found in the gradebook." << endl;
}

int main() {
    // Initialize the gradebook with an empty array and a size of 0
    Student students[10];
    int size = 0;

    // Main program loop
    while (true) {
        cout << "1. Add student\n2. View grades\n3. Remove student\n4. Quit" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                string name;
                cout << "Enter student's name: ";
                cin >> name;
                addStudent(students, size, name);
                break;
            case 2:
                viewGrades(students, size);
                break;
            case 3:
                string removeName;
                cout << "Enter student's name to remove: ";
                cin >> removeName;
                removeStudent(students, size, removeName);
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}