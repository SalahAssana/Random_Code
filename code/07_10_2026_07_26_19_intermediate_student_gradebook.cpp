#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Student struct to hold student name and grades
struct Student {
    string name;
    vector<int> grades;
};

// Function to calculate average grade for a student
double calculateAverageGrade(const Student& student) {
    int sum = 0;
    for (int grade : student.grades) {
        sum += grade;
    }
    return static_cast<double>(sum) / student.grades.size();
}

// Function to add student to the gradebook
void addStudent(vector<Student>& gradebook, const Student& newStudent) {
    gradebook.push_back(newStudent);
}

// Function to display the gradebook
void displayGradebook(const vector<Student>& gradebook) {
    for (const auto& student : gradebook) {
        cout << "Name: " << student.name << endl;
        cout << "Average Grade: " << calculateAverageGrade(student) << endl;
        cout << endl;
    }
}

int main() {
    // Initialize the gradebook
    vector<Student> gradebook;

    // Add students to the gradebook
    addStudent(gradebook, {"John", {90, 80, 95}});
    addStudent(gradebook, {"Jane", {85, 92, 88}});
    addStudent(gradebook, {"Bob", {78, 85, 90}});

    // Display the gradebook
    displayGradebook(gradebook);

    return 0;
}