% Collaborative Filtering Movie Recommender
%
% Author: [Your Name]
%
% Description: A collaborative filtering-based movie recommender system that uses user ratings and similarity metrics to recommend movies.

% Initialize necessary libraries and tools
import mlr.*
import statistics.*

% Load the MovieLens dataset (synthetic data can be used instead)
data = readtable('MovieLens.csv');

% Preprocess the data by converting ratings to numerical values and removing any rows with missing or invalid data
data.ratings = str2double(data.ratings);
data = removevars(data, 'genres');
data = rmmissing(data);

% Calculate the mean rating for each user
mean_ratings = groupby(data, 'user_id').mean('ratings');

% Calculate the covariance matrix of the ratings
cov_matrix = cov(data.ratings);

% Compute the similarity matrix using cosine similarity
similarity_matrix = zeros(size(cov_matrix));
for i = 1:size(cov_matrix, 1)
    for j = 1:size(cov_matrix, 2)
        if i ~= j
            similarity_matrix(i, j) = cov_matrix(i, :) * cov_matrix(:, j) / (norm(cov_matrix(i, :)) * norm(cov_matrix(:, j)));
        end
    end
end

% Recommend movies for each user based on the similarity matrix and mean ratings
recommended_movies = table();
for i = 1:size(data, 1)
    user_id = data.user_id{i};
    user_ratings = mean_ratings{user_id};
    similar_users = find(similarity_matrix(user_id, :));
    similar_user_ratings = mean_ratings{similar_users};
    recommended_movies = [recommended_movies; ...
        table(user_id, ...
            movie(title(data, :), 1), ...
            user_ratings + mean_ratings{similar_users}(2:end), ...
            'VariableNames', {'user_id', 'movie_title', 'recommendation'})];
end

% Print the recommended movies
fprintf('Recommended Movies:\n');
disp(recommended_movies);

% Save the recommended movies to a file (optional)
if ~exist('recommended_movies.csv', 'file')
    writetable(recommended_movies, 'recommended_movies.csv');
else
    warning('File "recommended_movies.csv" already exists. Recommendation results will not be saved.');
end

% End of script