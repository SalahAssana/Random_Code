#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
};

// Linked List class
class LinkedList {
private:
    Node* head; // Head of the linked list
public:
    LinkedList() : head(nullptr) {} // Constructor to initialize the linked list

    // Function to insert a new node at the end of the linked list
    void insert(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* lastNode = head;
            while (lastNode->next != nullptr) {
                lastNode = lastNode->next;
            }
            lastNode->next = newNode;
        }
    }

    // Function to delete a node with the given data
    void remove(int data) {
        if (head == nullptr) return;

        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->data != data) {
            current = current->next;
        }

        if (current->next == nullptr) return;

        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    // Function to search for a node with the given data
    bool search(int data) {
        Node* current = head;
        while (current != nullptr && current->data != data) {
            current = current->next;
        }
        return current != nullptr;
    }

    // Function to print the linked list
    void print() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    LinkedList myList;

    // Insert some nodes
    myList.insert(1);
    myList.insert(2);
    myList.insert(3);
    myList.insert(4);
    myList.insert(5);

    // Print the linked list
    myList.print();

    // Search for a node
    if (myList.search(3)) {
        cout << "Node 3 found." << endl;
    } else {
        cout << "Node 3 not found." << endl;
    }

    // Remove a node
    myList.remove(2);

    // Print the linked list again
    myList.print();

    return 0;
}