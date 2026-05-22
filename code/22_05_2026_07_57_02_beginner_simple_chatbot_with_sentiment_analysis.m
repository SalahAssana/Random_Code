% Simple Chatbot with Sentiment Analysis in MATLAB

% Import necessary libraries
import java.text.*; % for sentiment analysis
import java.util.*; % for text processing

% Define a simple chatbot that responds based on user input
function [response, sentiment] = chatbot(input)
    % Initialize response and sentiment variables
    response = '';
    sentiment = 0;

    % Check if the user wants to quit the conversation
    if strcmpi(input, 'quit') || strcmpi(input, 'exit')
        response = 'Goodbye!';
    % Analyze sentiment of the input message
    else
        % Convert input message to lowercase for simplicity
        input = lower(input);

        % Check if the input contains positive or negative words
        if strcontains(input, 'happy') || strcontains(input, 'joy')
            response = 'That''s great! I''m happy too!';
            sentiment = 1; % positive sentiment
        elseif strcontains(input, 'sad') || strcontains(input, 'unhappy')
            response = 'Sorry to hear that. You can talk about it if you want.';
            sentiment = -1; % negative sentiment
        else
            response = 'I don''t understand what you mean. Can you rephrase?';
            sentiment = 0; % neutral sentiment
        end
    end
end

% Main script to test the chatbot
if true
    % Initialize user input and response variables
    userInput = '';
    while strcmpi(userInput, 'quit') ~= true
        % Get user input
        disp('Enter a message or type "quit" to exit:');
        userInput = input('');
        
        % Run the chatbot with the user input
        [response, sentiment] = chatbot(userInput);
        
        % Display response and sentiment analysis
        disp(response);
        if sentiment > 0
            disp('Sentiment: Positive');
        elseif sentiment < 0
            disp('Sentiment: Negative');
        else
            disp('Sentiment: Neutral');
        end
    end