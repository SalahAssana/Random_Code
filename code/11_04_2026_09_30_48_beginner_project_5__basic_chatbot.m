% Project 5: Basic Chatbot
% Description: Develop a simple chatbot that responds to basic user queries using pre-defined rules and natural language processing techniques
% Complexity Level: BEGINNER

% Initialize chatbot responses
responses = {"Hello, I'm happy to help!", "That's interesting. What else do you want to talk about?", "I don't understand your question. Can you rephrase?"};

% Define the chatbot logic
function response = get_response(question)
    % Check if the question is asking for a greeting
    if contains(lower(question), 'hello') || contains(lower(question), 'hi')
        response = responses{1};
    % Check if the question is open-ended (starts with "what", "how", or "why")
    elseif contains(lower(question), 'what') || contains(lower(question), 'how') || contains(lower(question), 'why')
        response = responses{2};
    else
        response = responses{3};
    end
end

% Main chatbot loop
while true
    % Get user input
    question = input('You: ', 's');
    
    % Process the user input and generate a response
    response = get_response(lower(question));
    
    % Display the response
    disp(['Chatbot: ' response]);
end