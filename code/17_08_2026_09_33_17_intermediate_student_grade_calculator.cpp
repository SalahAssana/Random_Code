#include <iostream>
#include <vector>
#include <algorithm>

// Structure to represent a student's grade information
struct Grade {
    std::string name;
    double assignment1, assignment2, quiz1, quiz2, exam1, exam2;
};

// Function to calculate the average of a set of grades
double calculateAverage(double* grades, int count) {
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += grades[i];
    }
    return sum / count;
}

// Function to calculate the student's overall grade based on their assignments, quizzes, and exams
double calculateOverallGrade(const Grade& student) {
    double assignmentAverage = calculateAverage(&student.assignment1, 2);
    double quizAverage = calculateAverage(&student.quiz1, 2);
    double examAverage = calculateAverage(&student.exam1, 2);

    // Calculate the average of all grades (40% assignments, 20% quizzes, 40% exams)
    return (0.4 * assignmentAverage + 0.2 * quizAverage + 0.4 * examAverage) / 3;
}

int main() {
    std::vector<Grade> students = {
        {"John", 90.0, 85.0, 95.0, 92.0, 96.0, 98.0},
        {"Jane", 80.0, 75.0, 82.0, 88.0, 94.0, 91.0}
    };

    for (const auto& student : students) {
        double overallGrade = calculateOverallGrade(student);
        std::cout << "Student: " << student.name << ", Overall Grade: " << overallGrade << "\n";
    }

    return 0;
}