class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def append(self, value):
        new_node = Node(value)
        if not self.head:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node

    def display(self):
        current = self.head
        while current:
            print(current.value, end=" ")
            current = current.next
        print()

    def bubble_sort(self):
        if not self.head or not self.head.next:
            return
        current = self.head
        swapped = True
        while swapped:
            swapped = False
            current = self.head
            while current and current.next:
                if current.value > current.next.value:
                    current.value, current.next.value = current.next.value, current.value
                    swapped = True
                current = current.next

    def linear_search(self, target):
        current = self.head
        while current:
            if current.value == target:
                return current.value
            current = current.next
        return None

# Test the implementation
if __name__ == '__main__':
    linked_list = LinkedList()
    linked_list.append(5)
    linked_list.append(2)
    linked_list.append(8)
    linked_list.append(3)
    linked_list.append(1)

    print("Original Linked List:")
    linked_list.display()

    linked_list.bubble_sort()

    print("\nSorted Linked List:")
    linked_list.display()

    target = 8
    found_value = linked_list.linear_search(target)

    if found_value:
        print(f"\nFound {target} in the linked list: {found_value}")
    else:
        print(f"\n{target} not found in the linked list")