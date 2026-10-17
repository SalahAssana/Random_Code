#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string name;
    vector<int> grades;
};

double calculateAverageGrade(const Student& student) {
    int total = 0;
    for (int grade : student.grades) {
        total += grade;
    }
    return static_cast<double>(total) / student.grades.size();
}

void printStudentInfo(const Student& student, double averageGrade) {
    cout << "Name: " << student.name << endl;
    cout << "Average Grade: " << averageGrade << endl;
}

int main() {
    vector<Student> students = {
        {"John", {90, 80, 95}},
        {"Jane", {85, 92, 88}},
        {"Bob", {78, 76, 82}}
    };

    for (const auto& student : students) {
        double averageGrade = calculateAverageGrade(student);
        printStudentInfo(student, averageGrade);

        if (student.grades.size() < 3) {
            cout << "Warning: Missing grades for " << student.name << endl;
        }
    }

    return 0;
}