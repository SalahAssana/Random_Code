#include <iostream>
#include <string>
using namespace std;

struct StudentGrade {
    string name;
    double assignments; // 0-100
    double quizzes;     // 0-100
    double exams;       // 0-100
};

// Function to calculate student grade based on weighted average
double calculateStudentGrade(const StudentGrade& student) {
    // Calculate total points (assignments + quizzes + exams)
    double totalPoints = student.assignments + student.quizzes + student.exams;
    
    // Calculate weighted average
    double assignmentsWeightedAverage = (student.assignments / 100.0) * 20.0; // Assignments: 20%
    double quizzesWeightedAverage = (student.quizzes / 100.0) * 30.0;         // Quizzes: 30%
    double examsWeightedAverage = (student.exams / 100.0) * 50.0;           // Exams: 50%

    return totalPoints + assignmentsWeightedAverage + quizzesWeightedAverage + examsWeightedAverage;
}

int main() {
    StudentGrade student;

    cout << "Enter student name: ";
    cin >> student.name;

    cout << "Enter assignments grade (0-100): ";
    cin >> student.assignments;

    cout << "Enter quizzes grade (0-100): ";
    cin >> student.quizzes;

    cout << "Enter exams grade (0-100): ";
    cin >> student.exams;

    double calculatedGrade = calculateStudentGrade(student);

    cout << "Calculated Grade: " << calculatedGrade << endl;

    return 0;
}