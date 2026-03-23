% Simple Chatbot for Basic Conversations
% BEGINNER-level project to learn programming basics

% Define possible user inputs (strings) and their corresponding responses
inputs = ["hi", "hello", "how are you?", "what's up?"];
responses = ["Hello! How can I help you today?", "Hi there! What's on your mind?", "I'm doing well, thanks for asking. How about you?", "Not much, just hanging out."];

% Define the chatbot's current state (initially idle)
state = "idle";

% Main loop to interact with user
while true
    % Get user input (string)
    user_input = input("Chatbot: ", "s");
    
    % Check if user wants to quit (type 'quit' or 'q')
    if strcmpi(user_input, "quit") || strcmpi(user_input, "q")
        break;
        
    % Check for valid inputs and respond accordingly
    for i = 1:length(inputs)
        if strcmpi(user_input, inputs{i})
            fprintf("Chatbot: %s\n", responses{i});
            state = "idle";  % Reset chatbot's state after responding
            return;
        end
    end
    
    % If no valid input is found, respond with a default message
    if strcmpi(state, "idle")
        fprintf("Chatbot: Sorry, I didn't understand that. Try again!\n");
    else
        fprintf("Chatbot: Hmm... something went wrong. Let's start fresh!\n");
    end
    
    state = "idle";  % Reset chatbot's state after default response
end

fprintf("Chatbot: Thanks for chatting! Goodbye!\n");