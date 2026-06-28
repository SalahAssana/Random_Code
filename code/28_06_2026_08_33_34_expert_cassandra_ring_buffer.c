#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a ring buffer node
typedef struct {
    int data;
    struct Node* next;
} RingBufferNode;

// Function to create a new ring buffer node
RingBufferNode* create_node(int value) {
    RingBufferNode* node = (RingBufferNode*)malloc(sizeof(RingBufferNode));
    node->data = value;
    node->next = NULL;
    return node;
}

// Function to insert an element at the end of the ring buffer
void insert(RingBufferNode** head, int value) {
    RingBufferNode* new_node = create_node(value);
    if (*head == NULL || (*head)->data < new_node->data) {
        new_node->next = *head;
        *head = new_node;
    } else {
        RingBufferNode* current = *head;
        while (current->next != NULL && current->next->data > value) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Function to delete an element from the ring buffer
void delete_element(RingBufferNode** head, int key) {
    RingBufferNode* current = *head;
    if (current != NULL && current->data == key) {
        *head = current->next;
        free(current);
    } else {
        while (current != NULL && current->next != NULL && current->next->data != key) {
            current = current->next;
        }
        if (current != NULL && current->next != NULL) {
            RingBufferNode* temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
    }
}

// Function to search for an element in the ring buffer
int search(RingBufferNode* head, int key) {
    while (head != NULL) {
        if (head->data == key) {
            return 1;
        }
        head = head->next;
    }
    return -1;
}

// Function to print the ring buffer
void print_ring_buffer(RingBufferNode* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    RingBufferNode* head = NULL;
    int i;

    // Insert some elements
    for (i = 0; i < 10; i++) {
        insert(&head, i * 2);
    }

    // Print the ring buffer
    print_ring_buffer(head);

    // Delete an element
    delete_element(&head, 4);

    // Search for an element
    if (search(head, 6) == 1) {
        printf("Element found\n");
    } else {
        printf("Element not found\n");
    }

    return 0;
}