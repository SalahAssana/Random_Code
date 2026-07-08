% Predictive Text Input with N-Grams

classdef NGramPredictor < handle
    properties
        ngramMap
        wordList
    end
    
    methods
        function obj = NGramGramPredictor(ngramSize)
            % Initialize the n-gram map and word list
            obj.ngramMap = containers.Map();
            obj.wordList = {};
            
            % Load word list from file (synthetic data)
            [obj.wordList, ~] = textread('wordlist.txt', '%s');
        end
        
        function predictedWord = predict(obj, inputSequence)
            % Get the last n-gram
            lastNGram = obj.getNgram(inputSequence);
            
            % Find the most likely next word for the last n-gram
            [mostLikelyWord, ~] = findMostLikelyWord(lastNGram, obj.ngramMap);
            
            predictedWord = mostLikelyWord;
        end
        
        function ngram = getNgram(obj, sequence)
            % Convert the input sequence to lowercase
            sequence = lower(sequence);
            
            % Split the sequence into n-grams
            nGrams = splitSequenceIntoNGrams(sequence, obj.wordList, length(obj.wordList));
            
            % Get the last n-gram
            ngram = nGrams{end};
        end
        
        function [mostLikelyWord, probability] = findMostLikelyWord(ngram, ngramMap)
            % Find all possible next words for the given n-gram
            possibleNextWords = get PossibleNextWordsForNgram(ngram, ngramMap);
            
            % Calculate the probabilities for each possible next word
            [probabilities, ~] = calculateProbabilities(possibleNextWords, ngramMap);
            
            % Find the most likely next word and its probability
            [mostLikelyWord, index] = max(probabilities);
            mostLikelyWord = possibleNextWords{index};
            probability = probabilities(index);
        end
        
        function ngrams = splitSequenceIntoNGrams(sequence, wordList, length)
            % Split the sequence into n-grams of size 'length'
            ngrams = cell(0);
            for i = 1:length
                ngram = [sequence(i:i+length-1) ' '];
                ngrams{end+1} = ngram;
            end
        end
        
        function possibleNextWords = get PossibleNextWordsForNgram(ngram, ngramMap)
            % Get all possible next words for the given n-gram
            possibleNextWords = cell(0);
            keys = ngramMap.keys();
            for i = 1:length(keys)
                key = keys{i};
                if strmatch(lower(key), lower(ngram))
                    possibleNextWords{end+1} = key;
                end
            end
        end
        
        function probabilities = calculateProbabilities(possibleNextWords, ngramMap)
            % Calculate the probabilities for each possible next word
            probabilities = zeros(size(possibleNextWords));
            for i = 1:length(possibleNextWords)
                key = possibleNextWords{i};
                values = ngramMap.get(key);
                probabilities(i) = length(values)/length(obj.wordList);
            end
        end
    end
end

% Test the NGramPredictor class
if nargin == 0
    predictor = NGramPredictor(2);
    inputSequence = 'this is a test sentence';
    predictedWord = predictor.predict(inputSequence);
    fprintf('Predicted word: %s\n', predictedWord);
end