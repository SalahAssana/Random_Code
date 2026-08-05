% Recommendation Engine in MATLAB

% Import necessary libraries
import mlr.*

% Define the user rating matrix
user_ratings = {
    {'Movie1', 5; 'Movie2', 3; 'Movie3', 4; 'Movie4', 2},
    {'User1', [0, 0, 0, 0]; 'User2', [1, 1, 1, 0]; 'User3', [0, 0, 0, 1]}
};

% Define the product ratings
product_ratings = {
    {'Product1', [4, 5, 3]; 'Product2', [3, 3, 5]; 'Product3', [5, 4, 2]; 'Product4', [2, 3, 4]},
    {'Category1', [0.5, 0.7, 0.8; 0.6, 0.9, 0.5]}, % Category ratings
    {'Genre1', [0.8, 0.9; 0.6, 0.7]} % Genre ratings
};

% Define the recommendation parameters
num_recommendations = 3;
threshold = 0.4;

% Function to calculate similarity between users
function sim = user_similarity(user_ratings)
    num_users = size(user_ratings, 1);
    sim = zeros(num_users, num_users);
    
    for i = 1:num_users
        for j = (i+1):num_users
            sim(i, j) = sum(user_ratings{i} .* user_ratings{j}) / sqrt(sum(user_ratings{i}.^2)) * sqrt(sum(user_ratings{j}.^2));
        end
    end
end

% Function to make recommendations
function recs = recommend(user_ratings, product_ratings, num_recommendations)
    % Calculate the similarity matrix
    sim = user_similarity(user_ratings);
    
    % Get the target user's ratings
    target_user = 1; % Replace with desired user index
    
    % Calculate the weighted sum of similar users' ratings
    weights = sim(target_user, :);
    weights = weights ./ sum(weights);
    product_rated = product_ratings{2};
    weighted_sum = (weights .* product_rated)';
    
    % Get the unrated products for the target user
    unrated_products = find(product_rated == 0);
    
    % Make recommendations based on the weighted sum and threshold
    recs = [];
    for i = 1:size(unrated_products, 2)
        if weighted_sum(unrated_products(i)) >= threshold
            recs(end+1) = unrated_products(i);
        end
    end
    
    % Limit the number of recommendations
    recs = recs(1:min(length(recs), num_recommendations));
end

% Main script
if ~exist('user_ratings', 'file')
    user_ratings = {};
    product_ratings = {};
    
    for i = 1:10
        user_ratings{i} = {'Movie' + num2str(i), randi([0, 5], [4, 1])};
        product_ratings{i} = {'Product' + num2str(i), randi([0, 5], [3, 1])};
    end
    
    % Save the user ratings and product ratings
    save('user_ratings.mat', 'user_ratings');
    save('product_ratings.mat', 'product_ratings');
end

% Load the saved data if available
if exist('user_ratings.mat', 'file')
    load('user_ratings.mat', 'user_ratings');
else
    user_ratings = {};
    for i = 1:10
        user_ratings{i} = {'Movie' + num2str(i), randi([0, 5], [4, 1])};
    end
end

if exist('product_ratings.mat', 'file')
    load('product_ratings.mat', 'product_ratings');
else
    product_ratings = {};
    for i = 1:10
        product_ratings{i} = {'Product' + num2str(i), randi([0, 5], [3, 1])};
    end
end

% Make recommendations
recs = recommend(user_ratings, product_ratings, num_recommendations);

% Display the recommendations
fprintf('Recommended products:\n');
for i = 1:length(recs)
    fprintf('%s\n', recs{i});
end