#include <iostream>
#include <vector>
#include <stdexcept>

// Struct to represent a student's grade
struct StudentGrade {
    std::string name;
    double assignments;
    double quizzes;
    double exams;
};

// Function to calculate the final grade of a student
double calculateFinalGrade(const StudentGrade& student) {
    return (student.assignments + student.quizzes + student.exams) / 3.0;
}

// Function to validate input for each assignment, quiz, and exam score
bool validateScore(double score) {
    if (score < 0 || score > 100) {
        throw std::runtime_error("Invalid score: must be between 0 and 100");
    }
    return true;
}

int main() {
    // Create a vector to store student grades
    std::vector<StudentGrade> studentGrades;

    // Add some sample students' grades
    StudentGrade student1 = {"John", 85.5, 90.2, 95.8};
    StudentGrade student2 = {"Jane", 92.1, 88.4, 91.9};
    studentGrades.push_back(student1);
    studentGrades.push_back(student2);

    // Iterate over the students' grades and calculate their final grade
    for (const auto& student : studentGrades) {
        try {
            validateScore(student.assignments);
            validateScore(student.quizzes);
            validateScore(student.exams);
            double finalGrade = calculateFinalGrade(student);
            std::cout << "Student: " << student.name << ", Final Grade: " << finalGrade << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}