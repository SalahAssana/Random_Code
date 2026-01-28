% Simple Chatbot
% Author: [Your Name]

% Initialize chatbot response
response = '';

while true
    % Get user input
    user_input = input('Chatbot: ', 's');
    
    % Check for hi/bye commands
    if strcmpi(user_input, 'hi')
        response = 'Hello';
    elseif strcmpi(user_input, 'bye')
        response = 'Goodbye';
        break;
    else
        response = 'I don''t understand. Try again!';
    end
    
    % Display chatbot response
    fprintf('You: %s\nChatbot: %s\n', user_input, response);
    
    % Clear response for next interaction
    response = '';
end

% End of script