#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent student data
struct Student {
    string name;
    vector<double> grades; // Array of grades for assignments, projects, and exams
};

// Function to calculate the overall grade (average) for a student
double calculateOverallGrade(const Student& student) {
    double sum = 0.0;
    for (double grade : student.grades) {
        sum += grade;
    }
    return sum / student.grades.size();
}

// Function to calculate the letter grade based on the overall grade
char calculateLetterGrade(double overallGrade) {
    if (overallGrade >= 90) {
        return 'A';
    } else if (overallGrade >= 80) {
        return 'B';
    } else if (overallGrade >= 70) {
        return 'C';
    } else if (overallGrade >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

// Function to display student data and overall grade
void displayStudentData(const Student& student) {
    cout << "Student Name: " << student.name << endl;
    cout << "Grades: ";
    for (double grade : student.grades) {
        cout << grade << " ";
    }
    cout << endl;
    double overallGrade = calculateOverallGrade(student);
    char letterGrade = calculateLetterGrade(overallGrade);
    cout << "Overall Grade: " << overallGrade << endl;
    cout << "Letter Grade: " << letterGrade << endl;
}

int main() {
    // Synthetic data for demonstration purposes
    Student student1 = {"John", {85, 92, 78, 95}};
    Student student2 = {"Jane", {76, 88, 90, 80}};

    // Display student data and overall grade
    displayStudentData(student1);
    displayStudentData(student2);

    return 0;
}