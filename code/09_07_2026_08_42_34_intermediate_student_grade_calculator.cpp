#include <iostream>
#include <vector>

// Structure to represent a student's assignment
struct Assignment {
    std::string name;
    double score;
};

// Function to calculate student grade based on assignments
double calculateGrade(const std::vector<Assignment>& assignments) {
    double totalScore = 0.0;
    int totalWeight = 0;

    for (const auto& assignment : assignments) {
        totalScore += assignment.score * assignment.name.length();
        totalWeight += assignment.name.length();
    }

    if (totalWeight == 0) {
        return 0.0; // Default grade if no assignments
    }

    double averageScore = totalScore / totalWeight;
    if (averageScore >= 90) {
        return 4.0; // A grade
    } else if (averageScore >= 80) {
        return 3.5; // B+ grade
    } else if (averageScore >= 70) {
        return 3.0; // B grade
    } else if (averageScore >= 60) {
        return 2.5; // C+ grade
    } else if (averageScore >= 50) {
        return 2.0; // C grade
    } else {
        return 1.0; // F grade
    }
}

int main() {
    std::vector<Assignment> assignments = {
        {"Math", 85.0},
        {"Science", 90.0},
        {"English", 78.0}
    };

    double studentGrade = calculateGrade(assignments);

    std::cout << "Student's grade: " << studentGrade << std::endl;

    return 0;
}