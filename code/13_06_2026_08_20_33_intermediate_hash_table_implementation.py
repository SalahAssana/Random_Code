class Node:
    def __init__(self, key):
        self.key = key
        self.next = None


class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size

    def hash_function(self, key):
        return hash(key) % self.size

    def insert(self, key):
        index = self.hash_function(key)
        if not self.table[index]:
            self.table[index] = Node(key)
        else:
            current = self.table[index]
            while current.next:
                current = current.next
            current.next = Node(key)

    def search(self, key):
        index = self.hash_function(key)
        current = self.table[index]
        if not current:
            return None
        while current:
            if current.key == key:
                return current.key
            current = current.next
        return None

    def display(self):
        for i in range(len(self.table)):
            current = self.table[i]
            print(f"Index {i}: {'None' if not current else str(current.key)}", end=" ")
            while current:
                print(str(current.key), end=" ")
                current = current.next
            print()


if __name__ == '__main__':
    hash_table = HashTable(10)
    keys = [5, 2, 9, 6, 5, 3]
    for key in keys:
        hash_table.insert(key)
    hash_table.display()
    print(hash_table.search(5))