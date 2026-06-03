#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Structure to represent a student's grade
struct Grade {
    string course;
    double grade;
};

// Function to calculate the average grade for a student
double calculateAverageGrade(const vector<Grade>& grades) {
    double sum = 0.0;
    for (const auto& grade : grades) {
        sum += grade.grade;
    }
    return sum / grades.size();
}

// Function to generate a grade report for a student
string generateGradeReport(const vector<Grade>& grades) {
    string report = "Grade Report:\n";
    double averageGrade = calculateAverageAverage(grades);
    report += "Average Grade: " + to_string(averageGrade) + "\n";
    for (const auto& grade : grades) {
        report += grade.course + ": " + to_string(grade.grade) + "\n";
    }
    return report;
}

// Function to add a new grade for a student
void addGrade(vector<Grade>& grades, const string& course, double grade) {
    Grade newGrade = {course, grade};
    grades.push_back(newGrade);
}

int main() {
    vector<Grade> studentGrades;

    // Add some example grades
    addGrade(studentGrades, "Math", 85.0);
    addGrade(studentGrades, "Science", 92.0);
    addGrade(studentGrades, "English", 78.0);

    // Calculate and display the average grade
    double averageGrade = calculateAverageGrade(studentGrades);
    cout << "Average Grade: " << averageGrade << "\n";

    // Generate and display the grade report
    string gradeReport = generateGradeReport(studentGrades);
    cout << gradeReport;

    return 0;
}