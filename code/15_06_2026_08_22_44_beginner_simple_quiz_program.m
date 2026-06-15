% Simple Quiz Program in MATLAB
%
% This program asks users questions and keeps track of their scores.

score = 0; % Initialize score to zero
questions = ["What is the capital of France?", "Who is the CEO of Google?", ...
             "What is the largest planet in our solar system?"]; % Define questions
answers = ["Paris", "Sundar Pichai", "Jupiter"]; % Define answers

for i = 1:length(questions)
    question = questions{i};
    answer = input(strcat("What do you think is the ", question, "? "), 's');
    
    if strcmp(answer, answers{i})
        score = score + 1;
        disp("Correct!");
    else
        disp("Incorrect. The correct answer was: " + answers{i});
    end
end

disp("Your final score is: " + num2str(score) + "/" + num2str(length(questions)));