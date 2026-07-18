import heapq
import math
from collections import defaultdict

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq

def calculate_frequency(image):
    frequency = defaultdict(int)
    for pixel in image:
        for value in pixel:
            frequency[value] += 1
    return {char: freq for char, freq in frequency.items()}

def build_huffman_tree(frequency):
    heap = []
    for char, freq in frequency.items():
        node = Node(char, freq)
        heapq.heappush(heap, node)

    while len(heap) > 1:
        node1 = heapq.heappop(heap)
        node2 = heapq.heappop(heap)
        merged_node = Node(None, node1.freq + node2.freq)
        merged_node.left = node1
        merged_node.right = node2
        heapq.heappush(heap, merged_node)

    return heap[0]

def build_huffman_codes(node, prefix):
    if node.char is not None:
        huffman_codes[node.char] = prefix
    else:
        build_huffman_codes(node.left, prefix + "0")
        build_huffman_codes(node.right, prefix + "1")

def compress(image):
    frequency = calculate_frequency(image)
    huffman_tree = build_huffman_tree(frequency)
    huffman_codes = {}
    build_huffman_codes(huffman_tree, "")

    compressed_image = []
    for pixel in image:
        encoded_pixel = ""
        for value in pixel:
            encoded_pixel += huffman_codes[value]
        compressed_image.append(encoded_pixel)

    return compressed_image

def decompress(compressed_image):
    frequency = calculate_frequency(compressed_image)
    huffman_tree = build_huffman_tree(frequency)
    huffman_codes = {}
    build_huffman_codes(huffman_tree, "")

    decompressed_image = []
    for encoded_pixel in compressed_image:
        decoded_pixel = ""
        current_node = huffman_tree
        for bit in encoded_pixel:
            if bit == "0":
                current_node = current_node.left
            else:
                current_node = current_node.right
            if current_node.char is not None:
                decoded_pixel += str(current_node.char)
                current_node = huffman_tree
        decompressed_image.append(list(map(int, decoded_pixel)))

    return decompressed_image

if __name__ == '__main__':
    image = [[0, 1, 0], [1, 1, 1], [0, 1, 0]]
    compressed = compress(image)
    print(compressed)
    decompressed = decompress(compressed)
    print(decompressed)