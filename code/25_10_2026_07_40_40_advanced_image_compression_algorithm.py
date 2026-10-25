from PIL import Image
import zlib
import base64
import numpy as np

class Compressor:
    def __init__(self, img):
        self.img = img

    def compress(self):
        # Convert image to grayscale and quantize it
        gray = self.img.convert('L').point(lambda x: int(x/255)*255)
        q_img = gray.point(np.vectorize(lambda x: int(x*0.5)))
        
        # Calculate the DCT of each block
        dct_blocks = []
        for i in range(0, len(q_img), 8):
            for j in range(0, len(q_img[0]), 8):
                block = np.array([[(q_img[x][y] - 128) for y in range(j, j+8)] for x in range(i, i+8)])
                dct_block = self.dct(block)
                dct_blocks.append(dct_block)

        # Calculate the zig-zag order
        z_z_order = []
        for block in dct_blocks:
            z_z_order.append(self.zigzag(block))

        # Apply Huffman coding to each block
        encoded_blocks = []
        for block in z_z_order:
            huffman_tree = self.build_huffman_tree(block)
            encoded_block = self.encode_huffman(huffman_tree, block)
            encoded_blocks.append(encoded_block)

        return ''.join([base64.b64encode(zlib.compress(block)).decode('utf-8') for block in encoded_blocks])

    def decompress(self, compressed):
        # Decompress each block
        blocks = [zlib.decompress(base64.b64decode(compressed[i:i+compressed.index(b'\n', i)+1].encode('utf-8'))) for i in range(0, len(compressed), 4*10000)]
        
        # Inverse zig-zag and DCT for each block
        decompressed_blocks = []
        for block in blocks:
            inv_dct_block = self.idct(self.zigzag_inv(block))
            decompressed_blocks.append(inv_dct_block)

        # Reconstruct the original image
        reconstructed_img = np.zeros((len(decompressed_blocks), len(decompressed_blocks[0])))
        for i, block in enumerate(decompressed_blocks):
            for j, val in enumerate(block):
                reconstructed_img[i][j] = int(val) + 128

        return Image.fromarray(reconstructed_img.astype('uint8'))

    def dct(self, block):
        result = np.zeros((block.shape[0], block.shape[1]))
        for k in range(block.shape[0]):
            for l in range(block.shape[1]):
                sum_val = 0
                for m in range(block.shape[0]):
                    for n in range(block.shape[1]):
                        sum_val += block[m][n] * np.cos((2*m+1)*k/(block.shape[0]*2)) * np.cos((2*n+1)*l/(block.shape[1]*2))
                result[k][l] = np.sqrt(2/block.shape[0]/block.shape[1]) * sum_val
        return result

    def idct(self, block):
        result = np.zeros((block.shape[0], block.shape[1]))
        for k in range(block.shape[0]):
            for l in range(block.shape[1]):
                sum_val = 0
                for m in range(block.shape[0]):
                    for n in range(block.shape[1]):
                        sum_val += result[m][n] * np.cos((2*m+1)*k/(block.shape[0]*2)) * np.cos((2*n+1)*l/(block.shape[1]*2))
                result[k][l] = np.sqrt(2/block.shape[0]/block.shape[1]) * sum_val
        return result

    def zigzag(self, block):
        result = [None] * (block.shape[0] * block.shape[1])
        k = 0
        for i in range(block.shape[0]):
            if i % 2 == 1:
                for j in range(block.shape[1]-1, -1, -1):
                    result[k] = block[i][j]
                    k += 1
            else:
                for j in range(0, block.shape[1]):
                    result[k] = block[i][j]
                    k += 1
        return result

    def zigzag_inv(self, block):
        result = np.zeros((block.shape[0], block.shape[1]))
        k = 0
        for i in range(block.shape[0]):
            if i % 2 == 1:
                for j in range(block.shape[1]-1, -1, -1):
                    result[i][j] = block[k]
                    k += 1
            else:
                for j in range(0, block.shape[1]):
                    result[i][j] = block[k]
                    k += 1
        return result

    def build_huffman_tree(self, block):
        freq = {}
        for val in block:
            if val not in freq:
                freq[val] = 0
            freq[val] += 1
        huff_code = ''
        for val, count in sorted(freq.items(), key=lambda x: x[1], reverse=True):
            huff_code += '{0}: {1}'.format(val, self.encode_huffman_tree(val))
        return huff_code

    def encode_huffman(self, tree, block):
        encoded_block = ''
        for val in block:
            encoded_block += tree[val]
        return encoded_block

if __name__ == '__main__':
    img = Image.open('test.jpg')
    compressor = Compressor(img)
    compressed = compressor.compress()
    decompressed_img = compressor.decompress(compressed)
    decompressed_img.show()