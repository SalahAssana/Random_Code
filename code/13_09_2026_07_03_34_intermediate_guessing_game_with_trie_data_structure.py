class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        current = self.root
        for char in word:
            if char not in current.children:
                current.children[char] = TrieNode()
            current = current.children[char]
        current.is_end_of_word = True

    def suggestions(self, prefix):
        current = self.root
        for char in prefix:
            if char not in current.children:
                return []
            current = current.children[char]
        return self._suggestions(current, prefix)

    def _suggestions(self, node, prefix):
        words = []
        for char, child_node in sorted(node.children.items()):
            if child_node.is_end_of_word:
                words.append(prefix + char)
            words.extend(self._suggestions(child_node, prefix + char))
        return words

def main():
    trie = Trie()
    words = ["cat", "cats", "bat", "bats", "dog", "dogs"]
    for word in words:
        trie.insert(word)

    while True:
        print("Enter a prefix to get suggestions:")
        prefix = input().lower()
        if not prefix:
            break
        suggestions = trie.suggestions(prefix)
        if not suggestions:
            print(f"No suggestions found for {prefix}.")
        else:
            print(f"Suggestions for {prefix}:")
            for suggestion in suggestions:
                print(suggestion)

if __name__ == '__main__':
    main()