% Data Compression Algorithm using Huffman Coding

classdef DataCompression < handle
    methods
        function obj = DataCompression()
            % Initialize compression dictionary
            obj.compression_dict = containers.Map;
        end
        
        function compressed_data = compress(obj, input_data)
            % Calculate frequency of each character in the input data
            freq_map = freqCalc(input_data);
            
            % Build Huffman tree using frequencies
            huffman_tree = buildHuffmanTree(freq_map);
            
            % Encode data using Huffman tree
            encoded_data = encodeData(huffman_tree, input_data);
            
            % Compress data by replacing symbols with their corresponding codes
            compressed_data = compressData(encoded_data, huffman_tree);
        end
        
        function decompressed_data = decompress(obj, compressed_data)
            % Decompress data by replacing codes with their corresponding symbols
            decompressed_data = decompressData(compressed_data, obj.compression_dict);
        end
    end
    
    methods (Static)
        function freq_map = freqCalc(input_data)
            % Calculate frequency of each character in the input data
            freq_map = containers.Map;
            for i = 1:length(input_data)
                char_code = int2str(input_data(i));
                if isKey(freq_map, char_code)
                    freq_map(char_code) = freq_map(char_code) + 1;
                else
                    freq_map(char_code) = 1;
                end
            end
        end
        
        function huffman_tree = buildHuffmanTree(freq_map)
            % Build Huffman tree using frequencies
            queue = [];
            for k = setdiff(keys(freq_map), '0')
                queue = [queue struct('code', k, 'freq', freq_map{k})];
            end
            
            while length(queue) > 1
                left_node = minQueue(queue);
                right_node = minQueue(queue);
                queue = [queue struct('code', ['0' left_node.code], ...
                    'freq', left_node.freq + right_node.freq), ...
                    struct('code', ['1' right_node.code], ...
                    'freq', right_node.freq)];
            end
            
            huffman_tree = struct('code', '', 'freq', 0);
            current_node = huffman_tree;
            while ~isempty(queue)
                node = minQueue(queue);
                if strcmp(node.code(1), '0')
                    current_node.left = node;
                    current_node = node;
                else
                    current_node.right = node;
                    current_node = node;
                end
                queue = queue(2:end);
            end
        end
        
        function encoded_data = encodeData(huffman_tree, input_data)
            % Encode data using Huffman tree
            encoded_data = [];
            for i = 1:length(input_data)
                char_code = int2str(input_data(i));
                node = huffman_tree;
                while ~strcmp(node.code, '')
                    if strcmp(node.code(1), '0')
                        node = node.left;
                    else
                        node = node.right;
                    end
                end
                encoded_data = [encoded_data node.code];
            end
        end
        
        function compressed_data = compressData(encoded_data, huffman_tree)
            % Compress data by replacing symbols with their corresponding codes
            compressed_data = [];
            for i = 1:length(encoded_data)
                char_code = encoded_data(i);
                if strcmp(char_code(2:end), huffman_tree.code)
                    compressed_data = [compressed_data char_code(1)];
                else
                    compressed_data = [compressed_data char_code];
                end
            end
        end
        
        function decompressed_data = decompressData(compressed_data, compression_dict)
            % Decompress data by replacing codes with their corresponding symbols
            decompressed_data = [];
            for i = 1:length(compressed_data)
                code = compressed_data(i);
                node = findNode(compression_dict, code);
                if ~isempty(node.left) && strcmp(code(1), '0')
                    decompressed_data = [decompressed_data node.left.freq];
                elseif isempty(node.left) || strcmp(code(1), '1')
                    decompressed_data = [decompressed_data node.right.freq];
                end
            end
        end
        
        function node = findNode(compression_dict, code)
            % Find a node in the compression dictionary based on its code
            for k = keys(compression_dict)
                if strcmp(k, code)
                    node = struct('code', k, 'freq', compression_dict{k});
                    return;
                end
            end
        end
        
        function min_node = minQueue(queue)
            % Find the node with the minimum frequency in the queue
            min_freq = inf;
            min_node = [];
            for i = 1:length(queue)
                if queue(i).freq < min_freq
                    min_freq = queue(i).freq;
                    min_node = queue(i);
                end
            end
        end
    end
    
end

% Test the DataCompression class
if nargin == 0
    input_data = [48 49 50 51 52 53 54 55 56 57 58 59 60];
    obj = DataCompression();
    compressed_data = obj.compress(input_data);
    decompressed_data = obj.decompress(compressed_data);
    
    % Display the original and compressed data
    fprintf('Original data: ');
    for i = 1:length(input_data)
        fprintf('%d ', input_data(i));
    end
    fprintf('\n');
    
    fprintf('Compressed data: ');
    for i = 1:length(compressed_data)
        fprintf('%c', compressed_data(i));
    end
    fprintf('\n');
    
    % Display the decompressed data
    fprintf('Decompressed data: ');
    for i = 1:length(decompressed_data)
        fprintf('%d ', decompressed_data(i));
    end
    fprintf('\n');