class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

def reverse_recursive(head):
    if head is None or head.next is None:
        return head
    new_head = reverse_recursive(head.next)
    head.next.next = head
    head.next = None
    return new_head

def reverse_iterative(head):
    prev_node = None
    current_node = head
    while current_node and current_node.next:
        next_node = current_node.next
        current_node.next = prev_node
        prev_node = current_node
        current_node = next_node
    return prev_node

# Test the code
if __name__ == '__main__':
    # Create a linked list: 1 -> 2 -> 3 -> 4 -> 5
    head = Node(1)
    second = Node(2)
    third = Node(3)
    fourth = Node(4)
    fifth = Node(5)
    head.next = second
    second.next = third
    third.next = fourth
    fourth.next = fifth

    # Reverse the linked list using recursive approach
    reversed_head_recursive = reverse_recursive(head)

    # Print the reversed linked list using recursive approach
    current_node = reversed_head_recursive
    while current_node:
        print(current_node.value, end=" ")
        current_node = current_node.next
    print()

    # Reverse the linked list using iterative approach
    reversed_head_iterative = reverse_iterative(head)

    # Print the reversed linked list using iterative approach
    current_node = reversed_head_iterative
    while current_node:
        print(current_node.value, end=" ")
        current_node = current_node.next
    print()