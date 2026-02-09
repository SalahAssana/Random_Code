#include <iostream>
#include <vector>

// Function to calculate final grade based on scores and weights
double calculateFinalGrade(double score, double weight) {
    // Calculate weighted score
    double weightedScore = score * weight;
    
    // Calculate final grade (assuming max score is 100)
    double finalGrade = weightedScore / (weight * 100);
    
    return finalGrade;
}

// Function to calculate overall final grade for a student
double calculateOverallFinalGrade(std::vector<std::pair<double, double>>& scoresAndWeights) {
    double overallFinalGrade = 0.0;
    
    for (auto& scoreAndWeight : scoresAndWeights) {
        double score = scoreAndWeight.first;
        double weight = scoreAndWeight.second;
        
        // Calculate final grade for each subject and add to overall grade
        double subjectFinalGrade = calculateFinalGrade(score, weight);
        overallFinalGrade += subjectFinalGrade * weight;
    }
    
    return overallFinalGrade;
}

int main() {
    std::vector<std::pair<double, double>> studentScoresAndWeights = {
        {85.0, 0.3}, // Math
        {90.0, 0.2}, // Science
        {95.0, 0.3}, // English
        {80.0, 0.2}  // History
    };
    
    double overallFinalGrade = calculateOverallFinalGrade(studentScoresAndWeights);
    
    std::cout << "Student's overall final grade: " << overallFinalGrade * 100 << "%" << std::endl;
    
    return 0;
}