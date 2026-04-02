% Simple Chatbot with Finite State Machine
%
% Author: <Your Name>
%

% Initialize states
states = {'start', 'greet', 'ask', 'bye'};

% Initialize current state
currentState = 'start';

% Define the finite state machine
function [nextState, response] = chatbot(input)
    switch currentState
        case 'start'
            if strcmp(input, 'hi')
                nextState = 'greet';
                response = 'Hello! How are you?';
            else
                nextState = 'start';
                response = 'I didn''t understand. Try again!';
            end
        case 'greet'
            if strcmp(input, 'fine')
                nextState = 'ask';
                response = 'That''s good to hear. What do you want to talk about?';
            elseif strcmp(input, 'not fine')
                nextState = 'bye';
                response = 'Sorry to hear that. Goodbye!';
            else
                nextState = 'greet';
                response = 'I didn''t understand. Try again!';
            end
        case 'ask'
            if strcmp(input, 'weather')
                nextState = 'start';
                response = 'It''s sunny today! Let''s start the conversation again.';
            elseif strcmp(input, 'nothing')
                nextState = 'bye';
                response = 'Okay, goodbye then!';
            else
                nextState = 'ask';
                response = 'I didn''t understand. Try again!';
            end
        case 'bye'
            if strcmp(input, 'goodbye')
                nextState = 'start';
                response = 'Goodbye! Let''s start the conversation again.';
            else
                nextState = 'bye';
                response = 'Goodbye! That''s all for now.';
            end
    end
end

% Main script
while true
    % Ask user for input
    prompt = 'Chatbot: ';
    input = input(prompt, 's');
    
    % Run the chatbot
    [currentState, response] = chatbot(input);
    
    % Display response
    fprintf(response);
    fprintf('\n');
end