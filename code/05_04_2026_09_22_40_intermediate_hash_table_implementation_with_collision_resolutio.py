class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]

    def hash_function(self, key):
        return hash(key) % self.size

    def insert(self, key, value):
        index = self.hash_function(key)
        for pair in self.table[index]:
            if pair[0] == key:
                pair[1] = value
                return
        self.table[index].append((key, value))

    def search(self, key):
        index = self.hash_function(key)
        for pair in self.table[index]:
            if pair[0] == key:
                return pair[1]
        return None

    def delete(self, key):
        index = self.hash_function(key)
        for i, pair in enumerate(self.table[index]):
            if pair[0] == key:
                del self.table[index][i]
                return
        return None


# Test the hash table
if __name__ == '__main__':
    ht = HashTable(10)

    ht.insert("apple", 5)
    ht.insert("banana", 7)
    ht.insert("orange", 3)
    ht.insert("grape", 9)

    print(ht.search("banana"))  # Output: 7
    print(ht.search("grape"))    # Output: 9

    ht.delete("banana")
    print(ht.search("banana"))  # Output: None

    for key in ["apple", "orange", "grape"]:
        print(f"{key}: {ht.search(key)}")