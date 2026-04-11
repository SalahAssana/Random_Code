import random
import time
from collections import defaultdict

class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def insert(self, value):
        if not self.head:
            self.head = Node(value)
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = Node(value)

    def sort(self):
        current = self.head
        nodes = []
        while current:
            nodes.append(current.value)
            current = current.next

        nodes.sort()
        current = self.head
        for value in nodes:
            while current and current.value < value:
                current = current.next
            if not current:
                new_node = Node(value)
                self.head = new_node
            else:
                next_node = current.next
                current.next = Node(value)
                current = next_node

    def print_list(self):
        current = self.head
        while current:
            print(current.value, end=' ')
            current = current.next
        print()

def test_sorting_algorithm():
    ll = LinkedList()
    for _ in range(10000):
        value = random.randint(0, 100000)
        ll.insert(value)

    start_time = time.time()
    ll.sort()
    end_time = time.time()

    print("Sorting took {:.2f} seconds".format(end_time - start_time))
    ll.print_list()

if __name__ == '__main__':
    test_sorting_algorithm()