#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define a structure to hold data points
typedef struct {
    double x;
    double y;
} DataPoint;

// Function to calculate mean of an array of doubles
double mean(double *arr, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

// Function to calculate covariance of two arrays of doubles
double covariance(double *x, double *y, int n) {
    double mean_x = mean(x, n);
    double mean_y = mean(y, n);

    double cov = 0.0;
    for (int i = 0; i < n; i++) {
        cov += (x[i] - mean_x) * (y[i] - mean_y);
    }

    return cov / (n - 1);
}

// Function to calculate slope of a regression line
double slope(double *x, double *y, int n) {
    double covariance_xy = covariance(x, y, n);
    double variance_x = covariance(x, x, n);

    return covariance_xy / variance_x;
}

// Function to calculate intercept of a regression line
double intercept(double *x, double *y, int n) {
    double mean_x = mean(x, n);
    double slope_line = slope(x, y, n);

    return mean(y, n) - slope_line * mean_x;
}

// Function to generate synthetic data points
DataPoint* generate_data(int n) {
    DataPoint *data = (DataPoint *)malloc(n * sizeof(DataPoint));

    for (int i = 0; i < n; i++) {
        data[i].x = (double)i;
        data[i].y = 2.0 + 3.0 * sin(4.0 * M_PI * i / 180.0) + 0.5 * rand() / RAND_MAX;
    }

    return data;
}

// Function to print regression line equation
void print_regression_line(double slope, double intercept) {
    printf("y = %.2f x + %.2f\n", slope, intercept);
}

int main() {
    int n = 20; // Number of data points

    DataPoint *data = generate_data(n);

    double *x = (double *)malloc(n * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        x[i] = data[i].x;
        y[i] = data[i].y;
    }

    double slope_line = slope(x, y, n);
    double intercept_line = intercept(x, y, n);

    print_regression_line(slope_line, intercept_line);

    free(data);
    free(x);
    free(y);

    return 0;
}