#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a data point
typedef struct {
    double x;
    double y;
} DataPoint;

// Function to calculate the mean of an array
double mean(double* arr, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

// Function to calculate the covariance between two arrays
double cov(double* x, double* y, int n) {
    double mean_x = mean(x, n);
    double mean_y = mean(y, n);
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (x[i] - mean_x) * (y[i] - mean_y);
    }
    return sum / (n - 1);
}

// Function to perform linear regression
void linear_regression(DataPoint* data, int n, double* slope, double* intercept) {
    double cov_xy = cov(data->x, data->y, n);
    double variance_x = cov(data->x, data->x, n);
    *slope = cov_xy / variance_x;
    *intercept = mean(data->y, n) - (*slope) * mean(data->x, n);
}

// Function to print the results of linear regression
void print_results(double slope, double intercept) {
    printf("Slope: %f\n", slope);
    printf("Intercept: %f\n", intercept);
}

int main() {
    // Synthetic data points
    DataPoint data[5] = {{1.0, 2.0}, {2.0, 4.0}, {3.0, 6.0}, {4.0, 8.0}, {5.0, 10.0}};

    // Calculate the slope and intercept of the linear regression line
    double slope;
    double intercept;
    linear_regression(data, 5, &slope, &intercept);

    // Print the results
    print_results(slope, intercept);

    return 0;
}