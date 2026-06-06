#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a data point
typedef struct {
    double x;
    double y;
} DataPoint;

// Function to calculate the mean of an array of values
double mean(double* arr, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

// Function to calculate the covariance between two arrays of values
double covar(double* x, double* y, int n) {
    double mean_x = mean(x, n);
    double mean_y = mean(y, n);
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (x[i] - mean_x) * (y[i] - mean_y);
    }
    return sum / n;
}

// Function to calculate the variance of an array of values
double var(double* arr, int n) {
    double mean = mean(arr, n);
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (arr[i] - mean) * (arr[i] - mean);
    }
    return sum / n;
}

// Function to calculate the coefficients of a linear regression model
void linReg(DataPoint* data, int n, double* beta0, double* beta1) {
    double x_mean = mean(&data[0].x, n);
    double y_mean = mean(&data[0].y, n);
    *beta0 = y_mean;
    *beta1 = covar(&data[0].x, &data[0].y, n) / var(&data[0].x, n);
}

int main() {
    int n = 5;
    DataPoint data[n] = {{1.0, 2.0}, {2.0, 4.0}, {3.0, 6.0}, {4.0, 8.0}, {5.0, 10.0}};
    double beta0, beta1;
    linReg(data, n, &beta0, &beta1);
    printf("Coefficients: beta0 = %f, beta1 = %f\n", beta0, beta1);
    return 0;
}