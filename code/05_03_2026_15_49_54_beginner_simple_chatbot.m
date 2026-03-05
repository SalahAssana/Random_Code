% Simple Chatbot in MATLAB

% Define possible user queries
queries = ["hello", "hi", "goodbye", "see you later"];

% Define corresponding chatbot responses
responses = ["Hello! How can I help you?", "Hi there!", "Goodbye, have a nice day!", "See you later!"];

% Define the main function to interact with the user
function chatbot()
    % Initialize the conversation
    while true
        % Get the user input
        user_input = input("Chatbot: ");
        
        % Check if the user wants to quit
        if strcmpi(user_input, "goodbye") || strcmpi(user_input, "see you later")
            break;
        end
        
        % Find the matching query and respond accordingly
        for i = 1:length(queries)
            if strcmpi(user_input, queries{i})
                fprintf(responses{i});
                return
            end
        end
        
        % If no match found, provide a default response
        fprintf("Chatbot: Sorry, I didn't understand that. Try again!\n");
    end
    
    % End the conversation
    fprintf("Goodbye! Have a nice day!\n");
end

% Run the chatbot
chatbot();