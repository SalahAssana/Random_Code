import matplotlib.pyplot as plt
import numpy as np

class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def insert(self, value):
        new_node = Node(value)
        if not self.head:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node

    def visualize(self):
        values = []
        node = self.head
        while node:
            values.append(node.value)
            node = node.next
        plt.bar(range(len(values)), values)
        plt.xlabel('Index')
        plt.ylabel('Value')
        plt.title('Linked List Visualization')
        plt.show()

class Stack:
    def __init__(self):
        self.stack = []

    def push(self, value):
        self.stack.append(value)

    def pop(self):
        if not self.stack:
            return None
        return self.stack.pop()

    def visualize(self):
        values = [x for x in reversed(self.stack)]
        plt.bar(range(len(values)), values)
        plt.xlabel('Index')
        plt.ylabel('Value')
        plt.title('Stack Visualization')
        plt.show()

class Queue:
    def __init__(self):
        self.queue = []

    def enqueue(self, value):
        self.queue.append(value)

    def dequeue(self):
        if not self.queue:
            return None
        return self.queue.pop(0)

    def visualize(self):
        values = [x for x in self.queue]
        plt.bar(range(len(values)), values)
        plt.xlabel('Index')
        plt.ylabel('Value')
        plt.title('Queue Visualization')
        plt.show()

if __name__ == '__main__':
    linked_list = LinkedList()
    stack = Stack()
    queue = Queue()

    # Fill the data structures with some sample data
    for i in range(10):
        linked_list.insert(i)
        stack.push(i)
        queue.enqueue(i)

    # Visualize each data structure
    linked_list.visualize()
    stack.visualize()
    queue.visualize()