% Project 5: Text Analysis and Sentiment Detection
% Author: [Your Name]
% Date: [Date]

% Import necessary libraries
import java.io.File;
import java.io.FileReader;
import java.util.Scanner;

% Load the sentiment dictionary
sentiment_dict = load('sentiment_dict.mat');

% Define a function to preprocess text data
function preprocessed_text = preprocess_text(text)
    % Convert all text to lowercase
    preprocessed_text = lower(text);
    
    % Remove punctuation
    preprocessed_text = strrep(preprocessed_text, '[\p{P}]+', '');
    
    % Tokenize the text into individual words
    words = split(preprocessed_text, ' ');
    
    % Return the preprocessed text as a cell array of words
    preprocessed_text = words;
end

% Define a function to calculate sentiment score
function sentiment_score = calculate_sentiment(text)
    % Preprocess the text data
    preprocessed_text = preprocess_text(text);
    
    % Initialize the sentiment score
    sentiment_score = 0;
    
    % Loop through each word in the text
    for i = 1:length(preprocessed_text)
        % Check if the word is in the sentiment dictionary
        if ismember(preprocessed_text{i}, sentiment_dict.sentiment_words)
            % Get the sentiment value from the dictionary
            sentiment_value = sentiment_dict.sentiment_values(find(strcmp(sentiment_dict.sentiment_words, preprocessed_text{i}), 1));
            
            % Update the sentiment score based on the word's sentiment value
            if strcmp(preprocessed_text{i}, 'not')
                sentiment_score -= sentiment_value;
            else
                sentiment_score += sentiment_value;
            end
        end
    end
    
    % Normalize the sentiment score to a scale of -1 to 1
    sentiment_score = (sentiment_score - min(sentiment_dict.sentiment_values)) / (max(sentiment_dict.sentiment_values) - min(sentiment_dict.sentiment_values));
end

% Load sample text data
file_name = 'sample_text.txt';
text_data = importdata(file_name);

% Calculate the sentiment score for each piece of text
sentiment_scores = zeros(size(text_data, 1), 1);
for i = 1:size(text_data, 1)
    sentiment_score = calculate_sentiment(text_data.text{i});
    sentiment_scores(i) = sentiment_score;
end

% Print the sentiment scores
fprintf('Sentiment Score: %f\n', sentiment_scores);