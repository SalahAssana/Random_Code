#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Define a struct to represent a student
struct Student {
    string name;
    vector<double> grades; // store all grades for this student
};

// Function to calculate the average grade of a student
double calculateAverage(const Student& student) {
    double sum = 0.0;
    for (double grade : student.grades) {
        sum += grade;
    }
    return sum / student.grades.size();
}

// Function to generate a report for a student
string generateReport(const Student& student) {
    string report = "Student: " + student.name + "\n";
    double average = calculateAverage(student);
    report += "Average Grade: " + to_string(average) + "\n";
    return report;
}

// Function to add a new grade for a student
void addGrade(Student& student, double grade) {
    student.grades.push_back(grade);
}

// Main function
int main() {
    try {
        // Create some students and their grades
        Student john = {"John", {}};
        Student jane = {"Jane", {}};

        // Add grades for John
        addGrade(john, 85.0);
        addGrade(john, 92.0);
        addGrade(john, 78.0);

        // Add grades for Jane
        addGrade(jane, 90.0);
        addGrade(jane, 88.0);
        addGrade(jane, 95.0);

        // Generate reports for each student
        cout << generateReport(john) << endl;
        cout << generateReport(jane) << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1; // exit with error code
    }

    return 0;
}