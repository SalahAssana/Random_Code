#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Student {
    string name;
    vector<double> grades;
};

double calculateAverage(const vector<double>& grades) {
    double sum = 0;
    for (const auto& grade : grades) {
        if (grade < 0 || grade > 100) {
            throw runtime_error("Invalid grade: " + to_string(grade));
        }
        sum += grade;
    }
    return sum / grades.size();
}

void printStudentInfo(const Student& student, double averageGrade) {
    cout << "Name: " << student.name << endl;
    cout << "Average Grade: " << fixed << setprecision(2) << averageGrade << endl;
}

int main() {
    int numStudents;
    cout << "Enter the number of students: ";
    cin >> numStudents;

    vector<Student> students;
    for (int i = 0; i < numStudents; ++i) {
        Student student;
        cout << "Enter student name: ";
        cin.ignore(numeric_limits<streamsize>::max());
        getline(cin, student.name);

        int numGrades;
        cout << "Enter the number of grades for this student: ";
        cin >> numGrades;

        vector<double> grades(numGrades);
        for (int j = 0; j < numGrades; ++j) {
            double grade;
            cout << "Enter grade " << j + 1 << ": ";
            cin >> grade;
            grades.push_back(grade);
        }

        student.grades = grades;

        try {
            double averageGrade = calculateAverage(student.grades);
            printStudentInfo(student, averageGrade);
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            return 1; // Exit with error code
        }
    }

    return 0;
}