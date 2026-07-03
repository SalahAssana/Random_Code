class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

class BinarySearchTree:
    def __init__(self):
        self.root = None

    def insert(self, value):
        if not self.root:
            self.root = Node(value)
        else:
            self._insert(value, self.root)

    def _insert(self, value, node):
        if value < node.value:
            if node.left is None:
                node.left = Node(value)
            else:
                self._insert(value, node.left)
        elif value > node.value:
            if node.right is None:
                node.right = Node(value)
            else:
                self._insert(value, node.right)
        else:
            print("Value already exists in the tree.")

    def delete(self, value):
        self.root = self._delete(self.root, value)

    def _delete(self, node, value):
        if node is None:
            return node
        if value < node.value:
            node.left = self._delete(node.left, value)
        elif value > node.value:
            node.right = self._delete(node.right, value)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            else:
                min_value = self._find_min(node.right)
                node.value = min_value
                node.right = self._delete(node.right, min_value)
        return node

    def _find_min(self, node):
        current = node
        while current.left:
            current = current.left
        return current.value

    def traverse_in_order(self):
        result = []
        self._traverse_in_order(self.root, result)
        return result

    def _traverse_in_order(self, node, result):
        if node is not None:
            self._traverse_in_order(node.left, result)
            result.append(node.value)
            self._traverse_in_order(node.right, result)

    def traverse_pre_order(self):
        result = []
        self._traverse_pre_order(self.root, result)
        return result

    def _traverse_pre_order(self, node, result):
        if node is not None:
            result.append(node.value)
            self._traverse_pre_order(node.left, result)
            self._traverse_pre_order(node.right, result)

    def traverse_post_order(self):
        result = []
        self._traverse_post_order(self.root, result)
        return result

    def _traverse_post_order(self, node, result):
        if node is not None:
            self._traverse_post_order(node.left, result)
            self._traverse_post_order(node.right, result)
            result.append(node.value)

if __name__ == '__main__':
    bst = BinarySearchTree()
    values = [8, 3, 10, 1, 6, 14, 4, 7, 13]
    for value in values:
        bst.insert(value)
    print("In-order traversal: ", bst.traverse_in_order())
    print("Pre-order traversal: ", bst.traverse_pre_order())
    print("Post-order traversal: ", bst.traverse_post_order())