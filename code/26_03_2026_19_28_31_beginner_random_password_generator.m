% Random Password Generator
% Beginner complexity project

% Import necessary libraries
import java.util.Random;

% Set password length and character types
length = 12; % default length is 12 characters
chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=';

% Function to generate a random password
function password = generatePassword(length, chars)
    % Create a random number generator
    rng = java.util.Random();
    
    % Initialize an empty string for the password
    password = '';
    
    % Generate the password by looping 'length' times and appending a random character each time
    for i = 1:length
        password = strcat(password, chars(rng.nextInt(length(chars))));
    end
end

% Generate and display a random password
password = generatePassword(length, chars);
disp(password);