#include <iostream>
#include <vector>

// Define a struct to represent a student assignment
struct Assignment {
    std::string name;
    double grade;
    double weight; // relative importance of this assignment
};

// Function to calculate the average grade for a student
double calculateAverageGrade(const std::vector<Assignment>& assignments) {
    double totalGrade = 0.0;
    double totalWeight = 0.0;

    for (const auto& assignment : assignments) {
        totalGrade += assignment.grade * assignment.weight;
        totalWeight += assignment.weight;
    }

    return totalGrade / totalWeight;
}

int main() {
    // Define sample student assignments
    std::vector<Assignment> assignments = {
        {"Assignment 1", 85.0, 0.3},
        {"Assignment 2", 92.0, 0.4},
        {"Assignment 3", 78.0, 0.2},
        {"Assignment 4", 95.0, 0.1}
    };

    // Calculate and display the average grade
    double averageGrade = calculateAverageGrade(assignments);
    std::cout << "Average Grade: " << averageGrade << std::endl;

    return 0;
}
