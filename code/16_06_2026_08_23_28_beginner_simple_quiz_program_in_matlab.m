% Simple Quiz Program in MATLAB
% Beginner Level Implementation

% Initialize score to 0
score = 0;

% Define questions and answers
questions = {
    "Is the sky blue?", "yes";
    "Are you human?", "no";
    "Do dogs like treats?", "yes";
    "Can cats fly?", "no";
    "Is the sun a star?", "yes"
};

% Ask each question and update score accordingly
for i = 1:size(questions, 1)
    question = questions{i, 1};
    answer = input([question ' (yes/no)? '], 's');
    
    if strcmpi(answer, questions{i, 2})
        score = score + 1;
        disp('Correct!')
    else
        disp('Incorrect.')
    end
end

% Display final score
disp(['Your score is ' num2str(score) ' out of ' num2str(size(questions, 1)) '.']);