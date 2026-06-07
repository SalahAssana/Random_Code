#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    string name;
    vector<int> grades;
};

void calculateAverage(vector<Student>& students) {
    for (auto& student : students) {
        int sum = 0;
        for (int grade : student.grades) {
            sum += grade;
        }
        double average = static_cast<double>(sum) / student.grades.size();
        cout << "Student: " << student.name << ", Average Grade: " << fixed << setprecision(2) << average << endl;
    }
}

void displayHighestGrade(const vector<Student>& students) {
    int highestGrade = 0;
    string highestGradeStudentName;

    for (const auto& student : students) {
        for (int grade : student.grades) {
            if (grade > highestGrade) {
                highestGrade = grade;
                highestGradeStudentName = student.name;
            }
        }
    }

    cout << "Highest Grade Student: " << highestGradeStudentName << ", Highest Grade: " << highestGrade << endl;
}

int main() {
    vector<Student> students;

    // Synthetic data for demonstration
    students.push_back({{"John", {90, 80, 95}});
    students.push_back({{"Jane", {70, 85, 92}});
    students.push_back({{"Alice", {98, 95, 100}}});

    calculateAverage(students);
    displayHighestGrade(students);

    return 0;
}