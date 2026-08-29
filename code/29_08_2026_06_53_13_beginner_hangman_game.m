% Hangman Game in MATLAB

% Initialize word and guessed letters
word = 'apple';
guessed_letters = zeros(1, 5);
correct_guesses = 0;

while correct_guesses < length(word)
    % Display current state of word
    for i = 1:length(word)
        if guessed_letters(i) == 1
            fprintf('%c', word(i));
        else
            fprintf('_');
        end
    end
    fprintf('\n');

    % Ask user for a guess
    fprintf('Guess a letter: ');
    input_letter = input(''));

    % Check if the guessed letter is in the word
    found = 0;
    for i = 1:length(word)
        if word(i) == input_letter && guessed_letters(i) == 0
            guessed_letters(i) = 1;
            correct_guesses = correct_guesses + 1;
            found = 1;
        end
    end

    % If the letter is not in the word, draw a part of the hangman's gallows
    if ~found
        fprintf('Wrong guess!\n');
        switch correct_guesses
            case 0
                fprintf('\n   _____\n');
            case 1
                fprintf('\n   _____\n         |');
            case 2
                fprintf('\n   _____\n         |       ');
            case 3
                fprintf('\n   _____\n         |       \n     ^');
            case 4
                fprintf('\n   _____\n         |       \n     ^\n    /|');
        end
    end

    % Check if the game is over
    if correct_guesses == length(word)
        fprintf('Congratulations, you guessed the word!\n');
        break;
    elseif correct_guesses >= 5
        fprintf('Game over! The word was %s.\n', word);
        break;
    end
end