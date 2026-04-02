#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gnuplot-iostream.h"

// Define the structure for linear regression data point
typedef struct {
    double x;
    double y;
} DataPoint;

// Function to calculate the mean squared error (MSE)
double mse(double* predictions, double* actuals, int n) {
    double sum = 0.0;
    for(int i=0; i<n; i++) {
        sum += pow(actuals[i] - predictions[i], 2);
    }
    return sum / n;
}

// Function to perform gradient descent
void gradientDescent(double** X, double* y, int n, int d, double learning_rate, double* theta) {
    for(int j=0; j<d; j++) {
        double sum = 0.0;
        for(int i=0; i<n; i++) {
            sum += (X[i][j] - theta[j]) * (y[i] - (double)n);
        }
        theta[j] -= learning_rate * (1.0 / n) * sum;
    }
}

// Function to plot the regression line
void plotRegressionLine(double** X, double* y, int n, int d, double* theta) {
    Gnuplot gp;
    gp.send("set terminal png\n");
    gp.send("plot '-' with lines title 'Linear Regression'\n");
    for(int i=0; i<n; i++) {
        gp.send("%lf %lf\n", X[i][d-1], (double)n + theta[d-1]);
    }
    gp.send("e\n");
}

int main() {
    // Synthetic data generation
    int n = 100;
    double** X = (double**)malloc(n * sizeof(double*));
    for(int i=0; i<n; i++) {
        X[i] = (double*)malloc(2 * sizeof(double));
        X[i][0] = (double)i;
        X[i][1] = sin((double)i);
    }
    double* y = (double*)malloc(n * sizeof(double));
    for(int i=0; i<n; i++) {
        y[i] = X[i][1];
    }

    // Initial theta values
    double theta[2] = {0.0, 0.0};

    // Learning rate and number of iterations
    double learning_rate = 0.01;
    int num_iterations = 1000;

    for(int i=0; i<num_iterations; i++) {
        gradientDescent(X, y, n, 2, learning_rate, theta);
    }

    printf("Final theta values: [%.4f, %.4f]\n", theta[0], theta[1]);

    // Plot the regression line
    plotRegressionLine(X, y, n, 2, theta);

    return 0;
}