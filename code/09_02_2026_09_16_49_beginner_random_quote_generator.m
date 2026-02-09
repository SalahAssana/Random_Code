% Random Quote Generator

% Define quote structures
struct quote
    title = '';
    author = '';
    message = '';
end;

% Initialize quotes array
quotes = struct([]);

% Add some sample quotes
quotes(1) = struct('title', 'Believe You Can', ...
                   'author', 'Dr. Seuss', ...
                   'message', 'The greatest glory in living lies not in never falling, but rising every time.');
quotes(2) = struct('title', 'Life is Beautiful', ...
                   'author', 'Leo Tolstoy', ...
                   'message', 'We can't solve problems by using the same kind of thinking we used when we created them.');
quotes(3) = struct('title', 'The Future Belongs to Those Who Believe in the Beauty of Their Dreams', ...
                   'author', 'Eleanor Roosevelt', ...
                   'message', 'The future belongs to those who believe in the beauty of their dreams.');

% Define function to generate random quote
function randomQuote = getRandomQuote()
    % Randomly select a quote index
    idx = randi([1, size(quotes, 2)]);
    
    % Extract the selected quote
    randomQuote = quotes(idx);
end;

% Generate and display a random quote
randomQuote = getRandomQuote();
fprintf('"%s" by %s - "%s"\n', randomQuote.title, randomQuote.author, randomQuote.message);