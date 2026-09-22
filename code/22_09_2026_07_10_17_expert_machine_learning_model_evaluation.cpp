#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

// Helper functions
double mean(const vector<double>& values) {
    double sum = 0;
    for (const auto& value : values)
        sum += value;
    return sum / values.size();
}

double variance(const vector<double>& values, const double& meanValue) {
    double squaredDiffSum = 0;
    for (const auto& value : values)
        squaredDiffSum += pow(value - meanValue, 2);
    return squaredDiffSum / values.size();
}

double standardDeviation(const vector<double>& values, const double& meanValue) {
    return sqrt(variance(values, meanValue));
}

// Machine Learning Model Evaluation
class ModelEvaluator {
public:
    void evaluateModel(vector<vector<double>>& trainingData, vector<vector<double>>& testData,
                       vector<int>& predictedLabels, int numFolds) {
        // Cross-validation
        double totalAccuracy = 0;
        for (int fold = 0; fold < numFolds; ++fold) {
            // Split data into training and validation sets
            vector<vector<double>> trainDataFold(trainingData.begin() + fold,
                                                  trainingData.begin() + (fold + 1) * numFolds);
            vector<vector<double>> validateDataFold(trainingData.begin(),
                                                     trainingData.begin() + fold);
            for (int i = 0; i < (int)validateDataFold.size(); ++i)
                trainDataFold.insert(trainDataFold.end(), validateDataFold[i].begin(),
                                      validateDataFold[i].end());
            vector<vector<double>> testDataFold(testData.begin() + fold,
                                                testData.begin() + (fold + 1) * numFolds);
            for (int i = 0; i < (int)testDataFold.size(); ++i)
                trainDataFold.insert(trainDataFold.end(), testDataFold[i].begin(),
                                      testDataFold[i].end());
            
            // Train model
            // ...

            // Evaluate model on validation set
            int correctPredictions = 0;
            for (const auto& instance : validateDataFold) {
                double predictedValue = 0; // Predicted value using trained model
                if (predictedValue == instance.back())
                    ++correctPredictions;
            }
            double accuracy = static_cast<double>(correctPredictions) / validateDataFold.size();
            totalAccuracy += accuracy;

            // Clear memory to avoid unnecessary data copies
            trainDataFold.clear();
        }

        // Calculate overall model evaluation metrics
        double meanAccuracy = totalAccuracy / numFolds;
        double stdDeviationAccuracy = standardDeviation({totalAccuracy}, 0);

        cout << "Mean Accuracy: " << meanAccuracy << endl;
        cout << "Standard Deviation of Accuracy: " << stdDeviationAccuracy << endl;

        // Check if the model performed better than a random guess
        const int numClasses = 10; // Assuming binary classification for simplicity
        double chanceLevelAccuracy = static_cast<double>(correctPredictions) / testData.size();
        cout << "Chance Level Accuracy: " << chanceLevelAccuracy << endl;
    }
};

int main() {
    // Synthetic data generation (replace with your actual dataset)
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    vector<vector<double>> trainingData;
    for (int i = 0; i < 10000; ++i) {
        vector<double> instance(2);
        instance[0] = dis(gen); // Feature 1
        instance[1] = pow(dis(gen), 2); // Feature 2
        instance.push_back(static_cast<int>(dis(gen) > 0.5)); // Label (0 or 1)
        trainingData.push_back(instance);
    }

    vector<vector<double>> testData;
    for (int i = 0; i < 2000; ++i) {
        vector<double> instance(2);
        instance[0] = dis(gen); // Feature 1
        instance[1] = pow(dis(gen), 2); // Feature 2
        instance.push_back(static_cast<int>(dis(gen) > 0.5)); // Label (0 or 1)
        testData.push_back(instance);
    }

    vector<int> predictedLabels(2000);

    ModelEvaluator modelEvaluator;
    int numFolds = 10;
    modelEvaluator.evaluateModel(trainingData, testData, predictedLabels, numFolds);

    return 0;
}