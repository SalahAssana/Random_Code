% Define constants for SHA-256 algorithm
K = uint32([0x428a2f98 0x71374491 0xb5c0fbcf 0xe9b5dba5 ...
    0x3956af41 0x9609a3b7 0xe4d9b923 0xcb61dd93];
h = uint32([0x6a09e667 0xbb67ae85 0x3c6ef372 0xa54ff53a ...
    0x510e527f 0x9b4ac903 0xf2ffe18c 0x1fe34de2];

% Define function to calculate SHA-256 hash
function result = sha256(input)
    % Convert input to binary and pad with zeros
    padded_input = uint8([input; zeros(64 - length(input) * 8, 1)]);
    
    % Initialize variables for the algorithm
    w = zeros(64, 1);
    h_temp = zeros(8, 1);
    i = 0;
    
    % Loop through each 64-byte block of input
    while i <= length(padded_input) - 64
        % Initialize variables for the current block
        temp = zeros(16, 1);
        j = 0;
        
        % Loop through each 32-byte word in the block
        while j < 16
            temp(j+1) = typecast(typecast(padded_input(i+j*4+1: i+j*4+4), 'int8') + 256, 'uint32');
            j = j + 1;
        end
        
        % Initialize variables for the compression function
        a = h(1);
        b = h(2);
        c = h(3);
        d = h(4);
        e = h(5);
        f = h(6);
        g = h(7);
        h = h(8);
        
        % Loop through each round of the compression function
        for round = 1:64
            if round <= 19
                % Use rotation and XOR to combine words
                temp_rotated = uint32([temp(round) >> 2; temp(round) << 30]);
                a = (a + sbox(temp_rotated, K(1,round)) + e + c) mod 2^32;
                e = d;
                d = c;
                c = b;
                b = a;
            elseif round <= 39
                % Use rotation and XOR to combine words
                temp_rotated = uint32([temp(round-20) >> 13; temp(round-20) << 19]);
                a = (a + sbox(temp_rotated, K(2,round)) + f + e) mod 2^32;
                f = g;
                g = h;
                h = d;
                d = c;
                c = b;
            else
                % Use rotation and XOR to combine words
                temp_rotated = uint32([temp(round-40) >> 22; temp(round-40) << 10]);
                a = (a + sbox(temp_rotated, K(3,round)) + h + g) mod 2^32;
                h = f;
                f = e;
                e = d;
                d = c;
                c = b;
            end
            
            % Update variables for the next round
            a = (a >> 7 | a << 25);
            a = a + a + a;
        end
        
        % Calculate new hash values
        h(1) = (h(1) + a) mod 2^32;
        h_temp = uint32([h; temp]);
        
        % Update variables for the next block
        i = i + 64;
    end
    
    % Perform final compression and calculate the hash
    result = zeros(8, 1);
    for i = 1:8
        result(i) = sum(h_temp(i:i+3)) mod 2^32;
    end
end

% Define function to calculate S-box values
function result = sbox(input, K)
    % Calculate the S-box value
    result = uint32(0);
    
    for i = 1:8
        bit0 = (input & 0x80) >> 7;
        bit1 = (input & 0x40) >> 6;
        bit2 = (input & 0x20) >> 5;
        bit3 = (input & 0x10) >> 4;
        bit4 = (input & 0x08) >> 3;
        bit5 = (input & 0x04) >> 2;
        bit6 = (input & 0x02) >> 1;
        bit7 = input & 1;
        
        % Combine bits to form the S-box value
        result = (result + K(i,1)) mod 2^32;
        result = (result + bit0*bit5) mod 2^32;
        result = (result + bit1*bit4) mod 2^32;
        result = (result + bit3*bit7) mod 2^32;
    end
end

% Main script
input_file = 'test.txt';
output_file = 'sha256_hash.txt';

% Read input file and calculate the SHA-256 hash
file_id = fopen(input_file, 'r');
file_data = fread(file_id, '*char')';
fclose(file_id);
hash = sha256(file_data);

% Write the hash to a file
file_id = fopen(output_file, 'w');
fwrite(file_id, char(hash), '*char')';
fclose(file_id);