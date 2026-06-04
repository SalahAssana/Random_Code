% Recommendation System - EXPERT Complexity Project
% Author: [Your Name]

% Import necessary libraries
import mex;

% Define constants and parameters
R = 100; % Number of users
C = 500; % Number of items
n_factors = 50; % Number of factors in matrix factorization

% Synthetic data generation
user_item_matrix = rand(R, C);
user_factors = rand(R, n_factors);
item_factors = rand(C, n_factors);

% Define the recommendation function using collaborative filtering and matrix factorization
function recommendations = recommend(user_id, num_recommendations)
    % Get the user's factors
    user_factor_vector = user_factors(user_id, :);
    
    % Compute item similarities based on their factors
    item_similarity_matrix = zeros(C, C);
    for i = 1:C
        for j = 1:C
            if i ~= j
                item_similarity_matrix(i, j) = dot(item_factors(i, :), item_factors(j, :));
            end
        end
    end
    
    % Compute the weighted sum of item similarities and get the top N recommendations
    recommendations = zeros(num_recommendations, 1);
    for k = 1:num_recommendations
        [max_similarity, max_item_id] = max(item_similarity_matrix(:, user_id) .* (user_factor_vector' * item_factors));
        recommendations(k) = max_item_id;
        % Update the item similarity matrix to exclude already recommended items
        item_similarity_matrix(max_item_id, :) = 0;
    end
end

% Test the recommendation function
user_ids = 1:R;
num_recommendations = 5;

for user_id = user_ids
    recommendations = recommend(user_id, num_recommendations);
    fprintf('Recommendations for User %d:\n', user_id);
    disp(recommendations);
end