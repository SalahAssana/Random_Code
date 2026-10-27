% Project 5: Simple Recommender System
% Description: Create a simple recommender system using collaborative filtering to suggest products based on user ratings and preferences.

% Import necessary libraries
import java.util.*;

% Define the product categories
categories = ["Electronics", "Clothing", "Home Goods"];

% Define the users and their ratings for each product
usersRatings = {
    {"John", [4, 3, 5; 2, 1, 4; 3, 3, 2]},
    {"Alice", [5, 5, 1; 4, 2, 3; 2, 1, 5]},
    {"Bob", [3, 2, 4; 1, 5, 2; 4, 3, 1]}
};

% Function to calculate the similarity between two users
function sim = calcSimilarity(user1, user2)
    % Calculate the dot product of the two users' ratings
    dotProduct = sum(user1 .* user2);
    
    % Calculate the magnitude (Euclidean norm) of each user's ratings
    mag1 = sqrt(sum(user1 .^ 2));
    mag2 = sqrt(sum(user2 .^ 2));
    
    % Calculate the similarity using cosine similarity formula
    sim = dotProduct / (mag1 * mag2);
end

% Function to calculate the recommended products for a user
function recProducts = recommendProducts(user, topN)
    % Initialize an empty array to store the recommended products
    recProducts = {};
    
    % Iterate over all users and their ratings
    for i = 1:size(usersRatings, 2)
        % Skip the current user
        if strcmp(usersRatings{:, 1}, user)
            continue;
        
        % Calculate the similarity between the current user and the target user
        sim = calcSimilarity(usersRatings{i, 2}, usersRatings{find(strcmp(usersRatings(:, 1), user)), 2});
        
        % Iterate over all products rated by both users
        for j = 1:size(usersRatings{i, 2}, 1)
            if ~isnan(usersRatings{i, 2}(j))
                % Check if the product is already recommended or has been rated by the target user
                if isempty(recProducts) || ~ismember(j, recProducts{:}) && ~any(usersRatings{find(strcmp(usersRatings(:, 1), user)), 2}(j) > 0)
                    % Calculate the weighted average of the two users' ratings for the product
                    avgRating = (usersRatings{i, 2}(j) * sim + usersRatings{find(strcmp(usersRatings(:, 1), user)), 2}(j)) / (sim + 1);
                    
                    % Add the recommended product to the list
                    recProducts = [recProducts, j];
                end
            end
            
            % Stop recommending products when we have reached the top N
            if length(recProducts) >= topN
                break;
            end
        end
        
        % Stop iterating over users when we have reached the top N recommended products
        if length(recProducts) >= topN
            break;
        end
    end
    
    % Return the recommended products for the target user
    recProducts = reshape(unique(recProducts), 1, []);
end

% Main function to test the recommender system
function main()
    % Define the target user and the number of recommended products
    targetUser = "John";
    topN = 3;
    
    % Recommend products for the target user
    recProducts = recommendProducts(targetUser, topN);
    
    % Print the recommended products
    fprintf("Recommended products for %s:\n", targetUser);
    for i = 1:length(recProducts)
        fprintf("%d. %s\n", i, categories{recProducts(i)});
    end
end

% Run the main function when this script is executed
main();