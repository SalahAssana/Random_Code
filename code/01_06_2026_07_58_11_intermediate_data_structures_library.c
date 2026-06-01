#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
typedef struct node {
    int data;
    struct node* next;
} Node;

// Linked List structure
typedef struct LinkedList {
    Node* head;
    int size;
} LinkedList;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the end of the linked list
void insertNode(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (!list->head) {
        list->head = newNode;
    } else {
        Node* temp = list->head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    list->size++;
}

// Function to delete the node at a given position
void deleteNode(LinkedList* list, int position) {
    if (position < 0 || position >= list->size) {
        printf("Invalid position\n");
        return;
    }
    Node* temp = list->head;
    for (int i = 0; i < position - 1; i++) {
        temp = temp->next;
    }
    Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
    list->size--;
}

// Function to print the linked list
void printList(LinkedList* list) {
    Node* temp = list->head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    LinkedList list;
    list.head = NULL;
    list.size = 0;

    insertNode(&list, 1);
    insertNode(&list, 2);
    insertNode(&list, 3);

    printList(&list); // Output: 1 2 3

    deleteNode(&list, 1);

    printList(&list); // Output: 2 3

    return 0;
}