% Simple Quiz Program
% BEGINNER Complexity Level

% Define the quiz questions and answers
questions = {
    "What is the capital of France?", "Paris"
    "Who painted the Mona Lisa?", "Leonardo da Vinci"
    "What is 2 + 2?", "4"
};

correctAnswers = {
    "Paris", "Leonardo da Vinci", "4"
};

% Initialize score and question index
score = 0;
questionIndex = 1;

% Main quiz loop
while questionIndex <= length(questions)
    % Display the current question
    disp(questions{questionIndex});
    
    % Get user input
    userInput = input("Enter your answer: ", "s");
    
    % Check if the user's answer matches the correct answer
    if strcmp(userInput, correctAnswers{questionIndex})
        % Increment score and display correct message
        score = score + 1;
        disp("Correct!");
    else
        % Display incorrect message
        disp("Incorrect. The correct answer is: " + correctAnswers{questionIndex});
    end
    
    % Move to the next question
    questionIndex = questionIndex + 1;
end

% Display final score and congratulations message
disp("Quiz complete! Your final score is: " + num2str(score));