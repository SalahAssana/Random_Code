% Hangman Game
% Complexity Level: BEGINNER

% Define the word to guess
word = 'hello';

% Initialize the guessed letters and the number of incorrect guesses
guessed_letters = '';
incorrect_guesses = 0;

% Start the game loop
while true
    
    % Print the current state of the game
    fprintf('Guessed Letters: %s\n', guessed_letters);
    fprintf('Incorrect Guesses: %d\n', incorrect_guesses);
    
    % Ask the user for a letter to guess
    letter = input('Guess a letter: ', 's');
    
    % Check if the user has guessed the word
    if strcmp(word, guessed_letters)
        fprintf('Congratulations! You have guessed the word.\n');
        break;
    end
    
    % Check if the guessed letter is in the word
    if any(word == letter)
        % Add the correct letter to the guessed letters
        guessed_letters = [guessed_letters, letter];
    else
        % Increment the number of incorrect guesses
        incorrect_guesses = incorrect_guesses + 1;
        
        % Check if the user has made too many incorrect guesses
        if incorrect_guesses >= 6
            fprintf('Game over! The word was %s.\n', word);
            break;
        end
    end
end