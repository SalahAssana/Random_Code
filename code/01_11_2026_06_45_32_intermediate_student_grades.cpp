#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Student struct to hold student information
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

// Function to sort students by their average grades in descending order
void sortByAverageGrade(vector<Student>& students) {
    // Use a lambda function as the comparison function for sorting
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return calculateAverageGrade(a) > calculateAverageGrade(b);
    });
}

// Main function
int main() {
    vector<Student> students;

    // Add some synthetic data
    students.push_back({{"Alice", {90, 80, 95}});
    students.push_back({{"Bob", {85, 92, 88}});
    students.push_back({{"Charlie", {98, 96, 99}});

    // Calculate and display average grades for each student
    for (const auto& student : students) {
        double averageGrade = calculateAverageGrade(student);
        cout << "Student: " << student.name << ", Average Grade: " << averageGrade << endl;
    }

    // Sort students by their average grades in descending order
    sortByAverageGrade(students);

    // Display sorted students and their average grades
    for (const auto& student : students) {
        double averageGrade = calculateAverageGrade(student);
        cout << "Student: " << student.name << ", Average Grade: " << averageGrade << endl;
    }

    return 0;
}