#include <iostream>
#include <vector>
#include <cmath>
#include <random>

// Structure to represent a data point
struct DataPoint {
    double x, y;
};

// K-Means Clustering Algorithm Implementation
class KMeans {
public:
    // Constructor
    KMeans(int k, std::vector<DataPoint> points) : k_(k), points_(points), centroids_(k, {0.0, 0.0}) {}

    // Run the K-Means algorithm
    void run() {
        int iterations = 0;
        while (true) {
            assignments_.clear();
            calculateAssignments();

            if (!hasConverged()) break;

            updateCentroids();
            iterations++;
        }
        std::cout << "Converged in " << iterations << " iterations." << std::endl;
    }

private:
    // Calculate the assignment of each data point to a centroid
    void calculateAssignments() {
        for (const auto& point : points_) {
            double minDist = std::numeric_limits<double>::max();
            int closestCentroidIndex = -1;
            for (int i = 0; i < k_; ++i) {
                double dist = distance(point, centroids_[i]);
                if (dist < minDist) {
                    minDist = dist;
                    closestCentroidIndex = i;
                }
            }
            assignments_.push_back(closestCentroidIndex);
        }
    }

    // Check if the algorithm has converged
    bool hasConverged() {
        for (int i = 0; i < k_; ++i) {
            double oldX = centroids_[i].x;
            double oldY = centroids_[i].y;
            int count = 0;
            for (const auto& assignment : assignments_) {
                if (assignment == i) {
                    count++;
                    centroids_[i] = {{centroids_[i].x + points_[assignments_[count - 1]].x, centroids_[i].y + points_[assignments_[count - 1]].y}};
                }
            }
            if (std::abs(centroids_[i].x - oldX) > 0.001 || std::abs(centroids_[i].y - oldY) > 0.001) {
                return false;
            }
        }
        return true;
    }

    // Update the centroids based on the current assignments
    void updateCentroids() {
        for (int i = 0; i < k_; ++i) {
            int count = 0;
            DataPoint centroid({0.0, 0.0});
            for (const auto& assignment : assignments_) {
                if (assignment == i) {
                    count++;
                    centroid.x += points_[assignments_[count - 1]].x;
                    centroid.y += points_[assignments_[count - 1]].y;
                }
            }
            if (count > 0) {
                centroids_[i] = {centroid.x / count, centroid.y / count};
            }
        }
    }

    // Calculate the distance between two data points
    double distance(const DataPoint& p1, const DataPoint& p2) {
        return std::sqrt(std::pow(p1.x - p2.x, 2.0) + std::pow(p1.y - p2.y, 2.0));
    }

public:
    int k_;
    std::vector<DataPoint> points_;
    std::vector<int> assignments_;
    std::vector<DataPoint> centroids_;
};

int main() {
    // Synthetic data
    std::vector<DataPoint> points = {{1.0, 1.5}, {2.0, 3.0}, {4.0, 5.5}, {6.0, 7.0}, {8.0, 9.0}};
    KMeans kmeans(2, points);
    kmeans.run();
    return 0;
}