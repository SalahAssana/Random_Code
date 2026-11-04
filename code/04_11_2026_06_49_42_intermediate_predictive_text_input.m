% Predictive Text Input System
%
% Author: [Your Name]
%

function predictiveTextInput

    % Initialize word list and user input
    words = ["apple", "banana", "cherry", "date", "elderberry"];
    userInput = [];
    suggestedWords = [];

    while true
        % Display current user input
        disp(['Current Input: ' num2str(userInput)]);

        % Ask for next character or space
        userChar = input('Enter the next character (or press Enter to suggest words): ');

        if isempty(userChar)
            break;
        end

        % Update user input and suggested words based on last typed character
        [suggestedWords, userInput] = updateSuggestedWords(words, userChar, userInput);

        % Display suggested words
        disp(['Suggested Words: ' num2str(suggestedWords)]);
    end

    % Display final user input and suggested words
    disp(['Final Input: ' num2str(userInput)]);
    disp(['Final Suggested Words: ' num2str(suggestedWords)]);

end

function [suggestedWords, userInput] = updateSuggestedWords(words, userChar, userInput)

    % Initialize suggested words and updated user input
    suggestedWords = [];
    updatedUserInput = [userInput, userChar];

    % Find matching words based on last typed character
    for i = 1:length(words)
        if strmatch(lower(words{i}), lower(updatedUserInput), 'exact')
            suggestedWords = [suggestedWords, words{i}];
        end
    end

    % Sort and display suggested words
    suggestedWords = unique(suggestedWords);
    disp(['Suggested Words: ' num2str(suggestedWords)]);

end