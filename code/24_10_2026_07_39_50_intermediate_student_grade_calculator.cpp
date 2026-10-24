#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string name;
    double assignments; // weighted average (20%)
    double exams; // weighted average (40%)
    double attendance; // weighted average (40%)
};

double calculateGrade(double assignments, double exams, double attendance) {
    return (0.2 * assignments + 0.4 * exams + 0.4 * attendance);
}

void displayStudentGrade(Student student) {
    cout << "Name: " << student.name << endl;
    cout << "Assignments: " << student.assignments << endl;
    cout << "Exams: " << student.exams << endl;
    cout << "Attendance: " << student.attendance << endl;
    cout << "Grade: " << calculateGrade(student.assignments, student.exams, student.attendance) << endl;
}

int main() {
    vector<Student> students = {
        {"John", 85.0, 90.0, 95.0},
        {"Jane", 80.0, 88.0, 92.0}
    };

    for (Student& student : students) {
        displayStudentGrade(student);
        cout << endl;
    }

    return 0;
}