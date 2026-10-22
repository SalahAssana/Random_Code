% Hangman Game in MATLAB
% Author: <Your Name>

% Import necessary libraries
import java.util.*;

% Define the word list structure
struct WordList
    words
end

% Initialize the game state
gameState = struct('word', '', 'guessedLetters', '', 'incorrectGuesses', 0);

% Function to generate a random word from the word list
function word = getRandomWord(wordList)
    % Generate a random index for the word list
    idx = randi(size(wordList, 2));
    % Return the corresponding word
    word = wordList.words{idx};
end

% Function to check if the guessed letter is in the word
function isValidGuess = checkGuess(word, guess)
    % Initialize flag as false
    isValidGuess = false;
    
    % Check each character in the word for a match with the guessed letter
    for i = 1:length(word)
        if word(i) == guess
            % If found, set the flag to true and break the loop
            isValidGuess = true;
            break;
        end
    end
end

% Function to update the game state based on a valid guess
function gameState = updateGameState(gameState, guess)
    % Update the guessed letters string with the new guess
    gameState.guessedLetters = strcat(gameState.guessedLetters, guess);
    
    % Check if the word is fully guessed
    if all(ismember(gameState.word, guess))
        % If yes, set the game state as won
        gameState.incorrectGuesses = 0;
    end
end

% Function to update the game state based on an invalid guess
function gameState = updateGameStateInvalidGuess(gameState)
    % Increment the incorrect guesses count
    gameState.incorrectGuesses = gameState.incorrectGuesses + 1;
    
    % Check if the number of incorrect guesses exceeds a certain limit
    if gameState.incorrectGuesses > 5
        % If yes, set the game state as lost
        gameState.word = '';
    end
end

% Main script
wordList = struct('words', {'apple', 'banana', 'cherry', 'date', 'elderberry'});

gameState = struct('word', getRandomWord(wordList), 'guessedLetters', '', 'incorrectGuesses', 0);

while true
    % Display the current game state
    fprintf('Word: %s\nGuessed Letters: %s\nIncorrect Guesses: %d\n', gameState.word, gameState.guessedLetters, gameState.incorrectGuesses);
    
    % Ask for a guess from the user
    guess = input('Enter your guess: ', 's');
    
    % Check if the guess is valid
    isValidGuess = checkGuess(gameState.word, guess);
    
    % Update the game state based on the guess
    if isValidGuess
        gameState = updateGameState(gameState, guess);
    else
        gameState = updateGameStateInvalidGuess(gameState);
    end
    
    % Check if the game is over
    if isempty(gameState.word)
        break;
    end
end

% Display the final game state
fprintf('Game Over! The word was: %s\n', gameState.word);