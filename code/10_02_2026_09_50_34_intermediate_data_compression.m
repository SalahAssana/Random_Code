% Data Compression using Huffman Coding and Run-Length Encoding (RLE)

classdef DataCompression
    methods
        function obj = DataCompression()
            % Initialize variables for compression and decompression
            data = randi([0 1], 10000, 1);  % Synthetic binary data
            compressed_data = zeros(size(data));
            
            % Encode the data using Huffman Coding
            huffman_codes = generate_huffman_codes(data);
            encoded_data = encode_huffman(huffman_codes, data);
            
            % Compress the data using Run-Length Encoding (RLE)
            rle_compressed_data = run_length_encode(encoded_data);
            
            % Decompress and decode the data
            decompressed_data = run_length_decode(rle_compressed_data);
            decoded_data = decode_huffman(huffman_codes, decompressed_data);
            
            % Print the original and decompressed data
            fprintf('Original Data: %d\n', sum(data));
            fprintf('Decompressed Data: %d\n', sum(decoded_data));
        end
        
        function huffman_codes = generate_huffman_codes(data)
            % Generate Huffman codes for each unique symbol in the data
            [unique_symbols, ~] = unique(data);
            frequency = zeros(size(unique_symbols));
            for i = 1:length(unique_symbols)
                frequency(i) = sum(data == unique_symbols(i));
            end
            
            huffman_codes = cell(length(unique_symbols), 1);
            for i = 1:length(unique_symbols)
                code = '0';
                while true
                    if length(frequency) == 2
                        code = [code, '1'];
                        break;
                    elseif frequency(i) > frequency(1)
                        code = [code, '0'];
                    else
                        code = [code, '1'];
                    end
                    frequency([i, 1]) = frequency([i, 1]) - 1;
                end
                huffman_codes{i} = code;
            end
        end
        
        function encoded_data = encode_huffman(huffman_codes, data)
            % Encode the data using Huffman codes
            encoded_data = zeros(size(data));
            for i = 1:length(data)
                index = find(strcmp({huffman_codes{:}}, num2str(data(i))));
                encoded_data(i) = length(index);
            end
        end
        
        function rle_compressed_data = run_length_encode(data)
            % Compress the data using Run-Length Encoding (RLE)
            rle_compressed_data = zeros(size(data));
            for i = 1:length(data)
                if i > 1 && data(i) == data(i - 1)
                    rle_compressed_data(i) = rle_compressed_data(i - 1) + 1;
                else
                    rle_compressed_data(i) = data(i);
                end
            end
        end
        
        function decompressed_data = run_length_decode(data)
            % Decompress the data using Run-Length Decoding (RLE)
            decompressed_data = zeros(size(data));
            length = 1;
            for i = 1:length(data)
                if mod(length, 2) == 0
                    decompressed_data(i) = data(i);
                    length = 1;
                else
                    length = length + 1;
                end
            end
        end
        
        function decoded_data = decode_huffman(huffman_codes, data)
            % Decode the data using Huffman codes
            decoded_data = zeros(size(data));
            for i = 1:length(data)
                code = num2str(data(i));
                index = find(strcmp({huffman_codes{:}}, code));
                decoded_data(i) = unique_symbols(index);
            end
        end
    end
end

% Test the data compression and decompression
obj = DataCompression();