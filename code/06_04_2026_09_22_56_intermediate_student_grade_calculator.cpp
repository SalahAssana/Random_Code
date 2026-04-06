#include <iostream>
#include <vector>
#include <string>

// Struct to represent a student's grade
struct Grade {
    std::string name;
    double assignments;
    double quizzes;
    double exams;
};

// Function to calculate the overall grade average
double calculateGradeAverage(const Grade& student) {
    // Calculate the total grade points
    double total = student.assignments + student.quizzes + student.exams;

    // Calculate the number of assessments
    int numAssessments = 3;

    // Calculate the average grade
    return total / numAssessments;
}

// Function to display a student's grades
void displayStudentGrades(const Grade& student) {
    std::cout << "Student Name: " << student.name << std::endl;
    std::cout << "Assignments: " << student.assignments << std::endl;
    std::cout << "Quizzes: " << student.quizzes << std::endl;
    std::cout << "Exams: " << student.exams << std::endl;
    std::cout << "Overall Grade Average: " << calculateGradeAverage(student) << std::endl;
}

int main() {
    // Create a vector to store students' grades
    std::vector<Grade> students;

    // Add synthetic data for two students
    students.push_back({{"John", 85.0, 90.0, 95.0}});
    students.push_back({{"Jane", 75.0, 80.0, 92.5}});

    // Display each student's grades
    for (const auto& student : students) {
        displayStudentGrades(student);
        std::cout << std::endl;
    }

    return 0;
}