% Simple Chatbot in MATLAB
% Beginner Level Implementation

% Predefined responses for different user inputs
responses = {
    "I'm happy to help you! What's on your mind?", 
    "That's an interesting topic! Tell me more.", 
    "Sorry, I didn't quite understand. Please rephrase."
};

% Main loop for the chatbot
while true
    % Get user input (type 'quit' to exit)
    user_input = input('You: ', 's');
    
    % Check if user wants to quit
    if strcmp(user_input, 'quit')
        break
    
    % Basic rules-based response generation
    switch lower(user_input)
        case {'hello', 'hi'}
            disp(responses{1})
        case {'tell me a joke', 'joke'}
            disp('Why did the computer go to the doctor? Because it had a virus!')
        otherwise
            disp(responses{3})
    end
    
end

% Exit message when chatbot is stopped
disp('Goodbye! It was nice chatting with you.')