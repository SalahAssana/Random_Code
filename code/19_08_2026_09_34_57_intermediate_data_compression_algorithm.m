% LZW Compression Algorithm in MATLAB
%
% Author: [Your Name]

function lzw_compress()
    % Load sample text file
    file_id = fopen('example.txt', 'r');
    if (file_id == -1)
        error('File not found or unable to open');
    end
    
    % Read file content
    file_content = fscanf(file_id, '%c');
    fclose(file_id);
    
    % Initialize dictionary and codes array
    dict_size = 256; % ASCII characters
    dictionary = 0:dict_size-1;
    codes = uint8(0:dict_size-1);
    
    % Compress file content using LZW algorithm
    compressed_content = lzw_compress_algorithm(file_content, dictionary, codes);
    
    % Save compressed data to a file
    file_id = fopen('compressed_example.bin', 'w');
    if (file_id == -1)
        error('Unable to open output file for writing');
    end
    fwrite(file_id, compressed_content, 'uint8');
    fclose(file_id);
end

function compressed_data = lzw_compress_algorithm(input_string, dictionary, codes)
    % Initialize variables
    current_code = 0;
    longest_match_length = 0;
    compressed_data = uint16([]);
    
    % Main compression loop
    for i = 1:length(input_string)
        code = input_string(i);
        
        % Find the longest match in the dictionary
        [longest_match, longest_match_length] = find_longest_match(code, dictionary, codes, longest_match_length);
        
        % Add the current code to the compressed data
        if (current_code ~= 0)
            compressed_data = [compressed_data; current_code];
        end
        
        % Update the current code and the dictionary
        current_code = length(dictionary) + 1;
        dictionary = [dictionary; code];
        codes = [codes; code];
        
        % Update the longest match if a new longer match is found
        if (longest_match_length > i)
            longest_match_length = i;
        end
    end
    
    % Add the last code to the compressed data
    compressed_data = [compressed_data; current_code];
end

function [longest_match, longest_match_length] = find_longest_match(code, dictionary, codes, length)
    % Initialize variables
    longest_match = [];
    longest_match_length = 0;
    
    % Loop through the dictionary to find the longest match
    for i = 1:length(dictionary)
        if (dictionary(i) == code)
            match_length = i + 1;
            
            % Update the longest match if a new longer match is found
            if (match_length > longest_match_length)
                longest_match = code;
                longest_match_length = match_length;
            end
        end
    end
    
    % Check for matches in the codes array
    for i = 1:length(codes)
        if (codes(i) == code)
            match_length = i + 1;
            
            % Update the longest match if a new longer match is found
            if (match_length > longest_match_length)
                longest_match = code;
                longest_match_length = match_length;
            end
        end
    end
end

% Run the LZW compression algorithm
lzw_compress();