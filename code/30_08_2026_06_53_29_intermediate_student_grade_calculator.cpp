#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    vector<int> assignments;
    int quizScore;
    int examScore;
};

Student calculateGrade(const string& studentName, const vector<int>& assignmentScores, int quizScore, int examScore) {
    Student student = {studentName, {}, 0, 0};
    
    // Calculate total score for assignments
    int assignmentTotal = 0;
    for (int score : assignmentScores) {
        assignmentTotal += score;
    }
    
    // Calculate average assignment score
    double avgAssignmentScore = static_cast<double>(assignmentTotal) / assignmentScores.size();
    
    // Calculate overall grade based on assignments, quizzes, and exams
    int totalScore = assignmentTotal + quizScore + examScore;
    double overallGrade = (static_cast<double>(totalScore) / 3.0) * 100;
    
    student.assignments.push_back(assignmentTotal);
    student.quizScore = quizScore;
    student.examScore = examScore;
    student.name = studentName;
    
    return student;
}

int main() {
    Student student1 = calculateGrade("John", {80, 90, 70}, 85, 95);
    cout << "Student: " << student1.name << endl;
    cout << "Assignments: ";
    for (int score : student1.assignments) {
        cout << score << " ";
    }
    cout << endl;
    cout << "Quiz Score: " << student1.quizScore << endl;
    cout << "Exam Score: " << student1.examScore << endl;
    cout << "Overall Grade: " << fixed << setprecision(2) << student1.assignments[0] + student1.quizScore + student1.examScore / 3.0 * 100 << "%" << endl;
    
    return 0;
}