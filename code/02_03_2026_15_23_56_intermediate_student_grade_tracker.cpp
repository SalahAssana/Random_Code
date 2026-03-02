#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Structure to represent a student
struct Student {
    string name;
    vector<int> grades;
};

// Function to calculate average grade for a student
double calculateAverageGrade(const Student& student) {
    int total = 0;
    for (int grade : student.grades) {
        total += grade;
    }
    return static_cast<double>(total) / student.grades.size();
}

// Function to sort students by their average grades in descending order
void sortStudentsByAverageGrade(vector<Student>& students) {
    stable_sort(students.begin(), students.end(),
        [&](const Student& a, const Student& b) {
            return calculateAverageGrade(a) > calculateAverageGrade(b);
        });
}

// Function to print student information
void printStudent(const Student& student) {
    cout << "Name: " << student.name << endl;
    cout << "Grades: ";
    for (int grade : student.grades) {
        cout << grade << " ";
    }
    cout << endl;
    cout << "Average Grade: " << calculateAverageGrade(student) << endl;
}

// Function to add a new student
void addStudent(vector<Student>& students, const string& name, const vector<int>& grades) {
    Student newStudent = {name, grades};
    students.push_back(newStudent);
}

int main() {
    // Initialize students list
    vector<Student> students;

    // Add students
    addStudent(students, "John", {90, 80, 70});
    addStudent(students, "Alice", {95, 85, 75});
    addStudent(students, "Bob", {100, 90, 80});

    // Sort students by average grade
    sortStudentsByAverageGrade(students);

    // Print student information
    for (const auto& student : students) {
        printStudent(student);
    }

    return 0;
}