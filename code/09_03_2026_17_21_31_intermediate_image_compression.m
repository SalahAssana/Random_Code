% Image Compression using Huffman Coding and Run-Length Encoding
%
% Author: Your Name (Replace this line)
%

clear all; close all; clc;

% Define constants
IMG_WIDTH = 512;
IMG_HEIGHT = 512;
NUM_COLORS = 256;

% Load the image
img = imread('lena.png');
img = rgb2gray(img);
[img_height, img_width] = size(img);

% Convert image to binary array
binary_img = im2bw(img) .* 255;

% Compute Huffman coding
huffman_tree = huffman_tree(binary_img);

% Perform Run-Length Encoding (RLE)
rle_encoded = rle_encode(binary_img);

% Define compression ratios
ratios = [0.1, 0.3, 0.5];

% Compress the image using different compression ratios
for i = 1:length(ratios)
    ratio = ratios(i);
    compressed_img = compress_image(img, huffman_tree, rle_encoded, ratio);
    
    % Display the original and compressed images
    figure;
    subplot(121); imshow(img, []);
    title('Original Image');
    subplot(122); imshow(compressed_img, []);
    title(['Compressed Image with Ratio ' num2str(ratio)]);
end

% Function to compute Huffman coding
function huffman_tree = huffman_tree(binary_img)
    % Compute frequency of each symbol in the binary image
    freq = zeros(1, NUM_COLORS);
    for i = 1:img_height
        for j = 1:img_width
            freq(binary_img(i, j) + 1) = freq(binary_img(i, j) + 1) + 1;
        end
    end
    
    % Build the Huffman tree
    nodes = cell(1, length(freq));
    for i = 1:length(freq)
        nodes{i} = struct('freq', freq(i), 'left', [], 'right', []);
    end
    huffman_tree = build_huffman_tree(nodes);
end

% Function to perform Run-Length Encoding (RLE)
function rle_encoded = rle_encode(binary_img)
    % Initialize the RLE encoded array
    rle_encoded = zeros(size(binary_img));
    
    % Perform RLE encoding
    for i = 1:img_height
        for j = 1:img_width
            run_length = 0;
            while j + run_length < img_width && binary_img(i, j) == binary_img(i, j + run_length)
                run_length = run_length + 1;
            end
            rle_encoded(i, j) = run_length * binary_img(i, j);
        end
    end
end

% Function to compress the image using Huffman coding and RLE
function compressed_img = compress_image(img, huffman_tree, rle_encoded, ratio)
    % Initialize the compressed image array
    compressed_img = zeros(size(img));
    
    % Compress the image using Huffman coding and RLE
    for i = 1:img_height
        for j = 1:img_width
            if rand < ratio
                % Compress the current pixel using Huffman coding
                huffman_encoded = huffman_encode(binary_img(i, j), huffman_tree);
                compressed_img(i, j) = huffman_encoded;
            else
                % Use the original value for the current pixel
                compressed_img(i, j) = img(i, j);
            end
        end
    end
end

% Function to build the Huffman tree
function nodes = build_huffman_tree(nodes)
    while length(nodes) > 1
        % Find the two lowest-frequency nodes
        node1 = find_node_by_freq(nodes);
        node2 = find_node_by_freq(nodes);
        
        % Create a new internal node with the sum of frequencies
        internal_node = struct('freq', node1.freq + node2.freq, 'left', node1, 'right', node2);
        
        % Remove the two lowest-frequency nodes
        nodes = {internal_node};
    end
end

% Function to find the node with the lowest frequency
function node = find_node_by_freq(nodes)
    min_freq = inf;
    for i = 1:length(nodes)
        if nodes{i}.freq < min_freq
            min_freq = nodes{i}.freq;
            node = nodes{i};
        end
    end
end

% Function to encode a symbol using Huffman coding
function encoded_symbol = huffman_encode(symbol, tree)
    % Traverse the Huffman tree to find the code for the symbol
    if symbol == 0
        encoded_symbol = '0';
    else
        encoded_symbol = '1';
    end
    
    while tree.freq > 1
        if strcmp(encoded_symbol, '0')
            tree = tree.left;
        else
            tree = tree.right;
        end
        
        % Update the encoded symbol
        if strcmp(tree.left.freq > 1)
            encoded_symbol = [encoded_symbol, '0'];
        else
            encoded_symbol = [encoded_symbol, '1'];
        end
    end
    
    % The final encoded symbol is the leaf node's code
    encoded_symbol = [encoded_symbol, tree.code];
end

% Load the image file (replace with your own file)
%img = imread('lena.png');