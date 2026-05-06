#include <stdio.h>
#include <stdlib.h>

// Structure for priority queue element
typedef struct {
    int key;
    int value;
} PriorityQueueElement;

// Structure for priority queue
typedef struct {
    int capacity;
    int size;
    PriorityQueueElement* elements;
} PriorityQueue;

// Function to create a new priority queue with given capacity
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->elements = (PriorityQueueElement*)malloc(capacity * sizeof(PriorityQueueElement));
    return pq;
}

// Function to insert an element into the priority queue
void enqueue(PriorityQueue* pq, int key, int value) {
    if(pq->size == pq->capacity) {
        printf("Priority queue is full. Cannot enqueue.\n");
        return;
    }
    PriorityQueueElement newElement = {key, value};
    pq->elements[pq->size] = newElement;
    pq->size++;
}

// Function to remove the element with the highest priority from the priority queue
void dequeue(PriorityQueue* pq) {
    if(pq->size == 0) {
        printf("Priority queue is empty. Cannot dequeue.\n");
        return;
    }
    PriorityQueueElement temp = pq->elements[0];
    for(int i=1; i<pq->size; i++) {
        pq->elements[i-1] = pq->elements[i];
    }
    pq->size--;
}

// Function to get the highest priority element from the priority queue
void peek(PriorityQueue* pq) {
    if(pq->size == 0) {
        printf("Priority queue is empty. Cannot peek.\n");
        return;
    }
    PriorityQueueElement top = pq->elements[0];
    printf("Highest priority key: %d, value: %d\n", top.key, top.value);
}

// Function to print the elements of the priority queue
void printQueue(PriorityQueue* pq) {
    for(int i=0; i<pq->size; i++) {
        PriorityQueueElement element = pq->elements[i];
        printf("Key: %d, Value: %d\n", element.key, element.value);
    }
}

int main() {
    int capacity = 5;
    PriorityQueue* pq = createPriorityQueue(capacity);

    enqueue(pq, 1, 10);
    enqueue(pq, 2, 20);
    enqueue(pq, 3, 30);
    enqueue(pq, 4, 40);
    enqueue(pq, 5, 50);

    printQueue(pq);

    dequeue(pq);

    printQueue(pq);

    peek(pq);

    return 0;
}