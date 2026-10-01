% Hangman Game with Word Frequency
clear; close all;

% Initialize word frequency dictionary
word_freq = struct('word', [], 'freq', []);

% Load English words from file (use synthetic data if needed)
fileID = fopen('words.txt', 'r');
if fileID == -1
    error('File not found. Please provide a valid file name.')
end
while ~feof(fileID)
    line = fgetl(fileID);
    word = strtrim(line);
    [word_freq.num, ~] = size(word_freq);
    if word_freq.num < 1000 % limit to first 1000 words for demonstration purposes
        word_freq(word_freq.num + 1).word = word;
        word_freq(word_freq.num + 1).freq = 1; % initialize frequency to 1
    end
end
fclose(fileID);

% Initialize game variables
hidden_word = randperm(length(word_freq)) < 2; % choose a random word from the dictionary
game_word = word_freq{find(hidden_word, 1)};
game_word_length = length(game_word);
attempts = 0;
correct_guesses = zeros(1, game_word_length);

% Game loop
while true
    % Display current state of the word
    for i = 1:game_word_length
        if correct_guesses(i)
            fprintf('%c', game_word(i));
        else
            fprintf('_');
        end
    end
    fprintf('\n');

    % Ask for a guess
    guess = input('Enter your guess (or "quit" to exit): ', 's');

    % Handle quit command
    if strcmp(guess, 'quit')
        break;
    end

    % Check if the guess is in the word frequency dictionary
    found = false;
    for i = 1:length(word_freq)
        if contains(word_freq{i}.word, guess) && ~found
            % Suggest letters based on word frequency analysis
            suggested_letters = unique(strsplit(word_freq{i}.word, guess));
            fprintf('Suggested letters: %s\n', strjoin(suggested_letters, ', '));

            % Update game state if the guessed letter is in the word
            for j = 1:length(game_word)
                if game_word(j) == guess
                    correct_guesses(j) = 1;
                end
            end
        end
    end

    % Check if the game is won or lost
    if any(correct_guesses)
        fprintf('You win!\n');
        break;
    else
        attempts = attempts + 1;
        if attempts >= 6
            fprintf('Game over! The word was "%s".\n', game_word);
            break;
        end
    end
end

% Clean up
fclose all;