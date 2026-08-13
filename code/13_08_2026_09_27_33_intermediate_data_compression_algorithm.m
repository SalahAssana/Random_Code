% Data Compression Algorithm using Huffman Coding

function [] = huffman_encoding()
    % Read the data from a file
    [data] = read_data('example.txt');
    
    % Calculate the frequency of each symbol in the data
    freq = calculate_frequency(data);
    
    % Build the Huffman tree based on the frequencies
    root = build_huffman_tree(freq);
    
    % Traverse the Huffman tree and generate the compressed data
    encoded_data = traverse_huffman_tree(root, data);
    
    % Save the compressed data to a file
    save_compressed_data(encoded_data, 'compressed.txt');
end

function [data] = read_data(filename)
    % Read the data from a file
    fid = fopen(filename, 'r');
    if fid == -1
        error('File not found');
    end
    data = fscanf(fid, '%c');
    fclose(fid);
end

function freq = calculate_frequency(data)
    % Calculate the frequency of each symbol in the data
    symbols = unique(data);
    freq = zeros(size(symbols));
    for i = 1:length(symbols)
        freq(i) = sum(data == symbols(i));
    end
end

function root = build_huffman_tree(freq)
    % Build the Huffman tree based on the frequencies
    queue = [];
    heap = [];
    for i = 1:length(freq)
        if freq(i) > 0
            node = struct('symbol', i, 'freq', freq(i), 'left', [], 'right', []);
            enqueue(queue, node);
            heap = [heap, node];
        end
    end
    
    while length(heap) > 1
        left = dequeue(queue);
        right = dequeue(queue);
        parent = struct('symbol', '', 'freq', left.freq + right.freq, 'left', left, 'right', right);
        enqueue(queue, parent);
        heap = [heap(2:end), parent];
    end
    
    root = dequeue(queue);
end

function encoded_data = traverse_huffman_tree(root, data)
    % Traverse the Huffman tree and generate the compressed data
    encoded_data = '';
    for i = 1:length(data)
        current = root;
        while ~isempty(current.left) && current.symbol ~= data(i)
            if current.freq > current.left.freq
                current = current.right;
            else
                current = current.left;
            end
        end
        encoded_data = [encoded_data, int2str(current.symbol)];
    end
end

function save_compressed_data(encoded_data, filename)
    % Save the compressed data to a file
    fid = fopen(filename, 'w');
    if fid == -1
        error('File not found');
    end
    fprintf(fid, '%s', encoded_data);
    fclose(fid);
end

function node = dequeue(queue)
    % Dequeue an element from the queue
    node = queue(1);
    queue(1) = [];
end

function enqueue(queue, node)
    % Enqueue an element into the queue
    queue = [queue, node];
end

huffman_encoding();