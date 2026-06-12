% Word Frequency Analyzer

% Import necessary libraries
import java.util.HashMap;
import java.util.Map;

% Define function to calculate word frequencies
function [word_freq] = word_frequency(text)
    % Initialize frequency map
    freq_map = containers.Map();
    
    % Tokenize text into individual words
    words = textsplit(text);
    
    % Loop through each word and increment its frequency in the map
    for i = 1:length(words)
        word = lower(strtrim(words{i}));
        
        if iskey(freq_map, word)
            freq_map(word) = freq_map(word) + 1;
        else
            freq_map(word) = 1;
        end
    end
    
    % Return the frequency map as a struct array
    word_freq = struct();
    
    for i = 1:length(freq_map)
        word_freq(i).word = freq_map.keys{i};
        word_freq(i).frequency = freq_map.getnext(freq_map.keys{i});
    end
end

% Define function to split text into individual words
function words = textsplit(text)
    % Split the text by spaces and punctuation
    words = strsplit(text, ' ');
    
    % Remove any empty strings
    words = {words{:} ~=''};
end

% Load sample text data (replace with your own data as needed)
text_data = {'This is a test sentence.', 'Another test sentence. This is not the same.'};

% Calculate word frequencies for each piece of text
word_freqs = cell(1, length(text_data));
for i = 1:length(text_data)
    word_freqs{i} = word_frequency(text_data{i});
end

% Display the word frequencies for each piece of text
for i = 1:length(text_data)
    fprintf('Word frequencies for "%s":\n', text_data{i});
    for j = 1:length(word_freqs{i})
        fprintf('%s: %d\n', word_freqs{i}(j).word, word_freqs{i}(j).frequency);
    end
    fprintf('\n');
end