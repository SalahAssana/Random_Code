% Define the function to calculate the minimum number of scalar multiplications
function [min_scalar_multiplications, scalar_multiplication_order] = matrix_chain_multiplication(chain)
    n = length(chain);
    min_scalar_multiplications = zeros(n+1,n+1);
    scalar_multiplication_order = zeros(n+1);

    % Initialize base case for 1x1 and 2x2 matrices
    for i = 1:n
        min_scalar_multiplications(i,i) = 0;
    end

    % Fill up the matrix using dynamic programming
    for length = 3:n+1
        for i = 1:(n-length+2)
            j = i + (length-1);
            min_scalar_multiplications(i,j) = inf;
            for k = i:j-1
                q = min_scalar_multiplications(i,k) + min_scalar_multiplications(k+1,j) + chain(i)*chain(k)*chain(j);
                if q < min_scalar_multiplications(i,j)
                    min_scalar_multiplications(i,j) = q;
                    scalar_multiplication_order(i,j) = k;
                end
            end
        end
    end

    % Reconstruct the optimal order of matrix multiplications from the dynamic programming table
    function_order = [1 n];
    while length(function_order)>2
        i = function_order(1);
        j = function_order(end);
        k = scalar_multiplication_order(i,j);
        fprintf('Matrix %d * Matrix %d * Matrix %d\n',i,k+1,j);
        function_order([i+1 k+1]) = [];
    end

    % Return the minimum number of scalar multiplications and the optimal order
    [min_scalar_multiplications, scalar_multiplication_order]
end

% Test the function with a synthetic dataset
chain = [30 35 15 10 20 25];
[min_scalar_multiplications, scalar_multiplication_order] = matrix_chain_multiplication(chain);