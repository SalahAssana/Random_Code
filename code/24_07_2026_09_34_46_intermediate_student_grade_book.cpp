#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Student structure
struct Student {
    string name;
    int grades[5]; // assume 5 assignments
};

// Function to calculate average grade
double calculateAverage(Student student) {
    double sum = 0.0;
    for (int i = 0; i < 5; i++) {
        sum += student.grades[i];
    }
    return sum / 5.0;
}

// Function to add a new student
void addStudent(vector<Student>& students, string name) {
    Student newStudent;
    newStudent.name = name;
    for (int i = 0; i < 5; i++) {
        cout << "Enter grade for assignment " << i + 1 << ": ";
        cin >> newStudent.grades[i];
    }
    students.push_back(newStudent);
}

// Function to display student grades
void displayGrades(const vector<Student>& students) {
    for (const auto& student : students) {
        cout << "Name: " << student.name << endl;
        double average = calculateAverage(student);
        cout << "Average grade: " << average << endl;
        cout << "Grades: ";
        for (int i = 0; i < 5; i++) {
            cout << student.grades[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<Student> students;

    int choice;
    while (true) {
        cout << "1. Add a new student" << endl;
        cout << "2. Display all grades" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                string name;
                cout << "Enter student's name: ";
                cin >> name;
                addStudent(students, name);
                break;
            case 2:
                displayGrades(students);
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}