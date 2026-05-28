#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DATA 1000 // Maximum number of data points
#define MAX_FEATURES 3 // Maximum number of features per data point
#define K 5 // Number of clusters (K-Means algorithm)

// Structure to represent a data point
typedef struct {
    int features[MAX_FEATURES];
    float clusterIndex;
} DataPoint;

// Function to initialize the centroids randomly
void initCentroids(DataPoint centroids[], int K) {
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < MAX_FEATURES; j++) {
            centroids[i].features[j] = rand() % 100;
        }
        centroids[i].clusterIndex = (float)i / (K - 1.0);
    }
}

// Function to calculate the Euclidean distance between two points
float euclideanDistance(DataPoint p1, DataPoint p2) {
    float sum = 0;
    for (int i = 0; i < MAX_FEATURES; i++) {
        sum += pow(p1.features[i] - p2.features[i], 2);
    }
    return sqrt(sum);
}

// Function to update the centroids based on the data points
void updateCentroids(DataPoint* dataPoints, int K, DataPoint* centroids) {
    for (int i = 0; i < K; i++) {
        DataPoint newCentroid;
        float sumX = 0, sumY = 0;
        int count = 0;
        for (int j = 0; j < MAX_DATA; j++) {
            if (dataPoints[j].clusterIndex == centroids[i].clusterIndex) {
                sumX += dataPoints[j].features[0];
                sumY += dataPoints[j].features[1];
                count++;
            }
        }
        newCentroid.features[0] = sumX / count;
        newCentroid.features[1] = sumY / count;
        newCentroid.clusterIndex = (float)i / (K - 1.0);
        centroids[i] = newCentroid;
    }
}

// Function to assign each data point to the closest centroid
void assignClusters(DataPoint* dataPoints, DataPoint* centroids) {
    for (int i = 0; i < MAX_DATA; i++) {
        float minDistance = INFINITY;
        int clusterIndex = -1;
        for (int j = 0; j < K; j++) {
            float distance = euclideanDistance(dataPoints[i], centroids[j]);
            if (distance < minDistance) {
                minDistance = distance;
                clusterIndex = j;
            }
        }
        dataPoints[i].clusterIndex = (float)clusterIndex / (K - 1.0);
    }
}

// Function to calculate the total variance
float calculateTotalVariance(DataPoint* centroids, int K) {
    float sum = 0;
    for (int i = 0; i < MAX_DATA; i++) {
        DataPoint point = dataPoints[i];
        float minDistance = INFINITY;
        int clusterIndex = -1;
        for (int j = 0; j < K; j++) {
            float distance = euclideanDistance(point, centroids[j]);
            if (distance < minDistance) {
                minDistance = distance;
                clusterIndex = j;
            }
        }
        sum += pow(minDistance, 2);
    }
    return sum / (K * MAX_DATA);
}

int main() {
    // Initialize the data points
    DataPoint* dataPoints = (DataPoint*)malloc(MAX_DATA * sizeof(DataPoint));
    for (int i = 0; i < MAX_DATA; i++) {
        dataPoints[i].features[0] = rand() % 100;
        dataPoints[i].features[1] = rand() % 100;
        dataPoints[i].clusterIndex = -1.0;
    }

    // Initialize the centroids
    DataPoint* centroids = (DataPoint*)malloc(K * sizeof(DataPoint));
    initCentroids(centroids, K);

    int iterations = 0;
    float varianceThreshold = 0.01;

    while (true) {
        // Assign each data point to the closest centroid
        assignClusters(dataPoints, centroids);
        
        // Update the centroids based on the assigned clusters
        updateCentroids(dataPoints, K, centroids);

        // Calculate the total variance
        float variance = calculateTotalVariance(centroids, K);

        if (variance < varianceThreshold) {
            break;
        }
    }

    // Print the final centroids and their corresponding data points
    for (int i = 0; i < K; i++) {
        printf("Centroid %d: (%f, %f)\n", i, centroids[i].features[0], centroids[i].features[1]);
        int count = 0;
        for (int j = 0; j < MAX_DATA; j++) {
            if (dataPoints[j].clusterIndex == centroids[i].clusterIndex) {
                printf("Data point %d: (%d, %d)\n", j, dataPoints[j].features[0], dataPoints[j].features[1]);
                count++;
            }
        }
        printf("Count: %d\n", count);
    }

    // Free the memory
    free(dataPoints);
    free(centroids);

    return 0;
}