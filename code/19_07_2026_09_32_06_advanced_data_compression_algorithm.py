import heapq
from collections import defaultdict

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq


class HuffmanCoding:
    def __init__(self, text):
        self.text = text
        self.heap = []
        self.huffman_tree = None

    def calculate_frequency(self):
        frequency = defaultdict(int)
        for char in self.text:
            frequency[char] += 1
        return frequency

    def build_heap(self, frequency):
        for key in frequency:
            node = Node(key, frequency[key])
            heapq.heappush(self.heap, node)

    def merge_nodes(self):
        while len(self.heap) > 1:
            node1 = heapq.heappop(self.heap)
            node2 = heapq.heappop(self.heap)
            merged = Node(None, node1.freq + node2.freq)
            merged.left = node1
            merged.right = node2
            heapq.heappush(self.heap, merged)

    def build_huffman_tree(self):
        self.build_heap(self.calculate_frequency())
        self.merge_nodes()
        return self.heap[0]

    def huffman_encoding(self):
        if not self.huffman_tree:
            self.huffman_tree = self.build_huffman_tree()

        encoded_text = ""
        current_node = self.huffman_tree
        for char in self.text:
            if char == current_node.char:
                encoded_text += "1" if current_node.right else "0"
                current_node = current_node.left
            elif current_node.left and current_node.left.char == char:
                encoded_text += "1" if current_node.right else "0"
                current_node = current_node.left
            else:
                raise ValueError("Invalid character")

        return encoded_text

    def huffman_decoding(self, encoded_text):
        decoded_text = ""
        current_node = self.huffman_tree
        for bit in encoded_text:
            if bit == "1":
                current_node = current_node.right
            else:
                current_node = current_node.left
            if not current_node.left and not current_node.right:
                decoded_text += current_node.char
                current_node = self.huffman_tree

        return decoded_text


if __name__ == '__main__':
    text = "THIS IS AN EXAMPLE TEXT FOR HUFFMAN CODING"
    huffman_coding = HuffmanCoding(text)
    encoded_text = huffman_coding.huffman_encoding()
    print("Encoded Text:", encoded_text)

    decoded_text = huffman_coding.huffman_decoding(encoded_text)
    print("Decoded Text:", decoded_text)