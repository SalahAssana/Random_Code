% Simple Matrix Multiplication
% Author: [Your Name]

% Load necessary libraries
clear all; clc;
A = randi([0,1],2,3);  % Generate random matrix A (2x3)
B = randi([0,1],3,4);  % Generate random matrix B (3x4)

% Calculate the product of matrices A and B
C = A * B;

% Display the result
fprintf('Matrix C is:\n');
disp(C);