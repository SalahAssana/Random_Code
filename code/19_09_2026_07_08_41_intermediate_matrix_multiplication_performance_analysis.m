% Matrix Multiplication Performance Analysis
%
% This script compares the performance of matrix multiplication using
% built-in functions, NumPy, and OpenBLAS on different datasets.

% Import necessary libraries
import java.util.*

% Define function to generate random matrices
function A = genRandomMatrix(m, n)
    A = rand(m, n);
end

% Define function to measure execution time
function t = measureExecutionTime(fcn, varargin)
    tic;
    fcn(varargin{:});
    t = toc;
end

% Main script
script_start_time = clock;

% Set dimensions of matrices
m = 1000;
n = 1000;

% Generate random matrices
A = genRandomMatrix(m, n);
B = genRandomMatrix(n, m);

% Measure execution time for built-in function
t_builtin = measureExecutionTime(@times, A, B);

% Measure execution time for NumPy
import numpy as np
A_n = np.array(A);
B_n = np.array(B);
t_numpy = measureExecutionTime(@(a, b) a.dot(b), A_n, B_n);

% Measure execution time for OpenBLAS
import scipy.linalg as sla
t_openblas = measureExecutionTime(@sla.blas.dgemm, A, B);

% Display results
fprintf('Script started at %2.4f\n', script_start_time(1));
fprintf('Built-in function took %.4f seconds\n', t_builtin);
fprintf('NumPy took %.4f seconds\n', t_numpy);
fprintf('OpenBLAS took %.4f seconds\n', t_openblas);

script_end_time = clock;
fprintf('Script ended at %2.4f\n', script_end_time(1));