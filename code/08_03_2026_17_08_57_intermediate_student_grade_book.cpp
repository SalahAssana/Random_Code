#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Student structure
struct Student {
    string name;
    vector<int> grades;
};

// Function to add student
void addStudent(vector<Student>& students, string name) {
    Student newStudent = {"", {}};
    newStudent.name = name;
    students.push_back(newStudent);
}

// Function to remove student
bool removeStudent(vector<Student>& students, string name) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->name == name) {
            students.erase(it);
            return true;
        }
    }
    return false;
}

// Function to modify student grade
bool modifyStudentGrade(vector<Student>& students, string name, int grade) {
    for (auto& student : students) {
        if (student.name == name) {
            student.grades.push_back(grade);
            return true;
        }
    }
    return false;
}

// Function to search student by name
bool searchStudentByName(const vector<Student>& students, string name) {
    for (const auto& student : students) {
        if (student.name == name) {
            cout << "Found: " << student.name << endl;
            cout << "Grades: ";
            for (int grade : student.grades) {
                cout << grade << " ";
            }
            cout << endl;
            return true;
        }
    }
    return false;
}

// Function to print all students
void printAllStudents(const vector<Student>& students) {
    for (const auto& student : students) {
        cout << "Name: " << student.name << endl;
        cout << "Grades: ";
        for (int grade : student.grades) {
            cout << grade << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<Student> students = {};

    // Add students
    addStudent(students, "John");
    addStudent(students, "Alice");
    addStudent(students, "Bob");

    // Modify grades
    modifyStudentGrade(students, "John", 90);
    modifyStudentGrade(students, "Alice", 85);
    modifyStudentGrade(students, "Bob", 95);

    // Print all students
    cout << "All Students:" << endl;
    printAllStudents(students);

    // Search for student
    string searchName = "John";
    if (searchStudentByName(students, searchName)) {
        cout << "Found John." << endl;
    } else {
        cout << "Could not find John." << endl;
    }

    return 0;
}