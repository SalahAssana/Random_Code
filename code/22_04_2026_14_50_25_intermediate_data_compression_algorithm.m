% Data Compression Algorithm using Huffman Coding
%
% Author: Your Name (Replace this with your name)
%

function [compressed_data, huffman_tree] = huffman_encoding(input_data)

    % Generate a frequency dictionary for each unique character in the input data
    char_frequency = zeros(1, 256);
    for i = 1:length(input_data)
        char_frequency(input_data(i) + 1) = char_frequency(input_data(i) + 1) + 1;
    end

    % Find all non-zero frequencies and sort them by frequency in descending order
    [sorted_frequencies, sorted_chars] = sort(char_frequency(char_frequency > 0), 'descend');

    % Initialize the Huffman tree structure
    huffman_tree.children = cell(2^31 - 1, 1);
    huffman_tree.root = struct('left', [], 'right', []);

    % Build the Huffman tree recursively
    for i = 1:length(sorted_frequencies)
        if i == 1
            current_node.left = struct('symbol', sorted_chars(i), 'frequency', sorted_frequencies(i));
        elseif i == length(sorted_frequencies)
            current_node.right = struct('symbol', sorted_chars(i), 'frequency', sorted_frequencies(i));
        else
            [min_frequency, min_index] = min([sorted_frequencies(i - 1), sorted_frequencies(i)]);
            if min_frequency < sorted_frequencies(i + 1)
                huffman_tree.children(min_index) = struct('left', current_node);
                current_node = huffman_tree.children(min_index);
            else
                huffman_tree.children(min_index) = struct('right', current_node);
                current_node = huffman_tree.children(min_index);
            end
        end
    end

    % Initialize the compressed data structure
    compressed_data = zeros(1, length(input_data));

    % Encode the input data using Huffman coding
    for i = 1:length(input_data)
        node = huffman_tree.root;
        code = '';
        while true
            if isa(node.left, 'struct')
                code = strcat(code, '0');
                node = node.left;
            elseif isa(node.right, 'struct')
                code = strcat(code, '1');
                node = node.right;
            else
                compressed_data(i) = node.symbol - 1;
                break
            end
        end
    end

end

% Example usage:
input_data = ['this is an example for huffman encoding'];
[compressed_data, huffman_tree] = huffman_encoding(input_data);
disp(compressed_data);