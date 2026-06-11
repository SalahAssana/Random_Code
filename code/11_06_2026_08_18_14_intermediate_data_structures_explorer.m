% Data Structures Explorer
% Author: [Your Name]
% Date: [Current Date]

% Import necessary libraries
import java.util.*;

class DataStructuresExplorer {
    public static void main(String[] args) {
        // Create an array
        int[] myArray = {1, 2, 3, 4, 5};
        
        // Print the array
        System.out.println("Array: " + Arrays.toString(myArray));
        
        // Create a linked list
        LinkedList<Integer> myLinkedList = new LinkedList<>();
        
        // Add elements to the linked list
        myLinkedList.add(1);
        myLinkedList.add(2);
        myLinkedList.add(3);
        
        // Print the linked list
        System.out.println("Linked List: " + myLinkedList);
        
        // Create a tree structure
        Node root = new Node(1);
        root.left = new Node(2);
        root.right = new Node(3);
        
        // Traverse the tree and print its contents
        traverseTree(root);
    }

    public static void traverseTree(Node node) {
        if (node == null) {
            return;
        }
        
        System.out.println("Node value: " + node.value);
        
        traverseTree(node.left);
        traverseTree(node.right);
    }
}

class Node {
    int value;
    Node left;
    Node right;

    public Node(int value) {
        this.value = value;
    }
}