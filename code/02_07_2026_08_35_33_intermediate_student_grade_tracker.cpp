#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Student struct to hold student information
struct Student {
    string name;
    vector<double> grades; // store all grades
    double averageGrade; // calculate average grade on demand
};

// Function to add a new student with grades
void addStudent(vector<Student>& students, const string& name, const vector<double>& grades) {
    Student student;
    student.name = name;
    student.grades = grades;
    student.averageGrade = 0.0; // initialize average grade

    for (double grade : student.grades) {
        student.averageGrade += grade;
    }

    student.averageGrade /= student.grades.size(); // calculate average grade
    students.push_back(student);
}

// Function to display all students with their grades and averages
void displayStudents(const vector<Student>& students) {
    for (const Student& student : students) {
        cout << "Student: " << student.name << endl;
        cout << "Grades: ";
        for (double grade : student.grades) {
            cout << grade << " ";
        }
        cout << endl;
        cout << "Average Grade: " << student.averageGrade << endl;
        cout << endl;
    }
}

int main() {
    vector<Student> students;

    // Add some students with their grades
    addStudent(students, "John", {90.0, 80.0, 95.0});
    addStudent(students, "Alice", {85.0, 92.0, 78.0});
    addStudent(students, "Bob", {88.0, 89.0, 91.0});

    // Display all students with their grades and averages
    displayStudents(students);

    return 0;
}