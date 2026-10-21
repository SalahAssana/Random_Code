import heapq
from collections import defaultdict
import numpy as np
from PIL import Image

class Node:
    def __init__(self, char=None, freq=0):
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
    return frequency

def build_heap(frequency):
    heap = []
    for key in frequency:
        node = Node(key, frequency[key])
        heapq.heappush(heap, node)

    return heap

def merge_nodes(heap):
    while len(heap) > 1:
        node1 = heapq.heappop(heap)
        node2 = heapq.heappop(heap)

        merged = Node(None, node1.freq + node2.freq)
        merged.left = node1
        merged.right = node2

        heapq.heappush(heap, merged)

    return heap[0]

def build_codes_helper(root, current_code, codes):
    if root == None:
        return

    if root.char != None:
        codes[root.char] = current_code

    self.build_codes_helper(root.left, current_code + "0", codes)
    self.build_codes_helper(root.right, current_code + "1", codes)

def build_codes(root):
    codes = {}
    build_codes_helper(root, "", codes)
    return codes

def compress(image_path):
    image = np.array(Image.open(image_path))
    frequency = calculate_frequency(image)
    heap = build_heap(frequency)
    root = merge_nodes(heap)
    codes = build_codes(root)

    compressed_image = ""
    for pixel in image:
        for value in pixel:
            compressed_image += codes[value]

    return compressed_image

if __name__ == '__main__':
    compressed_image = compress("path_to_your_image.jpg")
    print(compressed_image)