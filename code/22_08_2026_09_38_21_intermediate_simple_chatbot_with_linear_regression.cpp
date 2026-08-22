#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct TrainingData {
    std::string input;
    double output;
};

double linearRegression(const std::vector<TrainingData>& data) {
    int n = data.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumXSq = 0;

    for (const auto& d : data) {
        sumX += static_cast<double>(d.input.length());
        sumY += d.output;
        sumXY += static_cast<double>(d.input.length()) * d.output;
        sumXSq += pow(static_cast<double>(d.input.length()), 2);
    }

    double m = (n * sumXY - sumX * sumY) / (n * sumXSq - pow(sumX, 2));
    double c = (sumY - m * sumX) / n;

    return c;
}

int main() {
    std::vector<TrainingData> trainingData = {
        {"hello", 0.5}, {"world", 0.8}, {"chatbot", 0.7},
        {"simple", 0.6}, {"linear", 0.9}
    };

    double predictedOutput = linearRegression(trainingData);

    std::cout << "Predicted output: " << predictedOutput << std::endl;

    return 0;
}