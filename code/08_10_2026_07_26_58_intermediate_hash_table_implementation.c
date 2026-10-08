#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for our hash table
typedef struct {
    int key;
    char* value;
} HashTableItem;

// Define the hash table structure
typedef struct {
    int size;
    int capacity;
    HashTableItem** items;
} HashTable;

// Function to calculate the hash of an integer key
int hash(int key, int capacity) {
    return key % capacity;
}

// Function to resize the hash table when it's full
void resize(HashTable* table) {
    int newCapacity = 2 * table->capacity;
    HashTableItem** newItems = (HashTableItem**)malloc(newCapacity * sizeof(HashTableItem*));
    for (int i = 0; i < table->capacity; i++) {
        if (table->items[i]) {
            int index = hash(table->items[i]->key, newCapacity);
            while (newItems[index] != NULL) {
                index = (index + 1) % newCapacity;
            }
            newItems[index] = table->items[i];
        }
    }
    free(table->items);
    table->items = newItems;
    table->capacity = newCapacity;
}

// Function to add an item to the hash table
void addItem(HashTable* table, int key, char* value) {
    if (table->size >= table->capacity) {
        resize(table);
    }
    int index = hash(key, table->capacity);
    for (int i = 0; i < table->capacity; i++) {
        if (!table->items[index]->value) {
            table->items[index]->key = key;
            table->items[index]->value = value;
            table->size++;
            return;
        }
        index = (index + 1) % table->capacity;
    }
}

// Function to get an item from the hash table
char* getItem(HashTable* table, int key) {
    int index = hash(key, table->capacity);
    for (int i = 0; i < table->capacity; i++) {
        if (table->items[index]->key == key) {
            return table->items[index]->value;
        }
        index = (index + 1) % table->capacity;
    }
    return NULL;
}

// Function to print the hash table
void printTable(HashTable* table) {
    for (int i = 0; i < table->capacity; i++) {
        if (table->items[i]) {
            printf("Key: %d, Value: %s\n", table->items[i]->key, table->items[i]->value);
        }
    }
}

// Main function
int main() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = 0;
    table->capacity = 10;
    table->items = (HashTableItem**)malloc(table->capacity * sizeof(HashTableItem*));
    for (int i = 0; i < table->capacity; i++) {
        table->items[i] = NULL;
    }

    addItem(table, 1, "apple");
    addItem(table, 2, "banana");
    addItem(table, 3, "cherry");
    addItem(table, 4, "date");

    printTable(table);

    char* value = getItem(table, 2);
    printf("Value for key 2: %s\n", value);

    return 0;
}