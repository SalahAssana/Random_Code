#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a struct to represent student information
struct Student {
    string name;
    vector<int> grades;
};

// Function to calculate average grade for a student
double calcAverageGrade(const Student& student) {
    int total = 0;
    for (int grade : student.grades) {
        total += grade;
    }
    return static_cast<double>(total) / student.grades.size();
}

// Function to print the student report
void printStudentReport(const Student& student, double averageGrade) {
    cout << "Name: " << student.name << endl;
    cout << "Average Grade: " << fixed << setprecision(2) << averageGrade << endl;
}

int main() {
    // Create a vector to store student information
    vector<Student> students = {
        {"Alice", {85, 90, 78}},
        {"Bob", {92, 88, 95}},
        {"Charlie", {80, 75, 85}}
    };

    // Calculate and print the report for each student
    for (const auto& student : students) {
        double averageGrade = calcAverageGrade(student);
        cout << "Student Report:" << endl;
        printStudentReport(student, averageGrade);
        cout << endl;
    }

    return 0;
}