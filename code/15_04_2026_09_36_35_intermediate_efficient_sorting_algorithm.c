#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for nodes in linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node with given data
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the end of the list
void append(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* lastNode = *head;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
}

// Function to print the linked list
void printList(Node* head) {
    printf("Linked List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to merge two sorted lists into one
Node* mergeLists(Node* list1, Node* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    Node* mergedList = NULL;
    if (list1->data <= list2->data) {
        mergedList = list1;
        list1 = list1->next;
    } else {
        mergedList = list2;
        list2 = list2->next;
    }

    Node* current = mergedList;
    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            current->next = list1;
            list1 = list1->next;
        } else {
            current->next = list2;
            list2 = list2->next;
        }
        current = current->next;
    }

    current->next = (list1 != NULL) ? list1 : list2;
    return mergedList;
}

// Function to mergeSort an array of integers using linked lists
void mergeSort(int arr[], int n) {
    Node* head = NULL;
    for (int i = 0; i < n; i++) {
        append(&head, arr[i]);
    }

    // Base case: if the list contains only one node
    if (head == NULL || head->next == NULL) return;

    Node* midNode = head;
    for (int i = 1; i <= n/2; i++) {
        midNode = midNode->next;
    }
    Node* secondHalfHead = midNode->next;
    midNode->next = NULL;

    // Recursively sort the two halves
    mergeSort(head, n/2);
    mergeSort(secondHalfHead, n - n/2);

    // Merge the sorted halves into one
    head = mergeLists(head, secondHalfHead);
}

// Function to print the array
void printArray(int arr[], int n) {
    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int n = 10;
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    printf("Original array: ");
    printArray(arr, n);

    mergeSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}