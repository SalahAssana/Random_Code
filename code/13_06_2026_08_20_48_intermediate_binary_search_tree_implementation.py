class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def insert(self, key):
        if not self.root:
            self.root = Node(key)
        else:
            self._insert(key, self.root)

    def _insert(self, key, node):
        if key < node.key:
            if node.left:
                self._insert(key, node.left)
            else:
                node.left = Node(key)
        elif key > node.key:
            if node.right:
                self._insert(key, node.right)
            else:
                node.right = Node(key)

    def delete(self, key):
        self.root = self._delete(key, self.root)

    def _delete(self, key, node):
        if not node:
            return node
        if key < node.key:
            node.left = self._delete(key, node.left)
        elif key > node.key:
            node.right = self._delete(key, node.right)
        else:
            if not node.left or not node.right:
                return None
            if not node.right:
                return node.left
            if not node.left:
                return node.right
            min_node = self._find_min(node.right)
            node.key = min_node.key
            node.right = self._delete(min_node.key, node.right)
        return node

    def _find_min(self, node):
        while node.left:
            node = node.left
        return node

    def inorder_traversal(self):
        result = []
        self._inorder_traversal(self.root, result)
        return result

    def _inorder_traversal(self, node, result):
        if node:
            self._inorder_traversal(node.left, result)
            result.append(node.key)
            self._inorder_traversal(node.right, result)

if __name__ == '__main__':
    bst = BST()
    keys = [50, 30, 20, 40, 70, 60, 80]
    for key in keys:
        bst.insert(key)
    print("In-order traversal of the given tree is")
    print(bst.inorder_traversal())
    print("\nDeleting 20")
    bst.delete(20)
    print("In-order traversal after deletion of 20")
    print(bst.inorder_traversal())