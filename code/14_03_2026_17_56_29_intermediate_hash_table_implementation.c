#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for hash table node
typedef struct {
    char* key;
    char* value;
} HashNode;

// Define the structure for hash table
typedef struct {
    int size; // Size of the hash table
    int capacity; // Capacity of the hash table
    HashNode** table; // Pointer to array of hash nodes
} HashTable;

// Function to calculate the index for a given key
int hashFunction(char* key, int capacity) {
    int sum = 0;
    int i = 0;
    while (key[i] != '\0') {
        sum += key[i];
        i++;
    }
    return sum % capacity;
}

// Function to create a new hash table with given size
HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->capacity = size * 2; // Initial capacity is double the size
    table->table = (HashNode**)calloc(table->capacity, sizeof(HashNode*));
    return table;
}

// Function to insert a key-value pair into the hash table
void insert(HashTable* table, char* key, char* value) {
    int index = hashFunction(key, table->capacity);
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = strdup(key);
    node->value = strdup(value);
    table->table[index] = node;
}

// Function to search for a key in the hash table
char* search(HashTable* table, char* key) {
    int index = hashFunction(key, table->capacity);
    HashNode* node = table->table[index];
    while (node != NULL && strcmp(node->key, key) != 0) {
        node = node->next;
    }
    if (node == NULL || strcmp(node->key, key) != 0) {
        return NULL; // Key not found
    } else {
        return node->value;
    }
}

// Function to delete a key-value pair from the hash table
void delete(HashTable* table, char* key) {
    int index = hashFunction(key, table->capacity);
    HashNode* node = table->table[index];
    HashNode* prev = NULL;
    while (node != NULL && strcmp(node->key, key) != 0) {
        prev = node;
        node = node->next;
    }
    if (node == NULL || strcmp(node->key, key) != 0) {
        // Key not found
    } else {
        free(node->key);
        free(node->value);
        if (prev == NULL) {
            table->table[index] = node->next;
        } else {
            prev->next = node->next;
        }
        free(node);
    }
}

// Function to print the hash table
void printHashTable(HashTable* table) {
    int i;
    for (i = 0; i < table->capacity; i++) {
        HashNode* node = table->table[i];
        while (node != NULL) {
            printf("%s -> %s\n", node->key, node->value);
            node = node->next;
        }
    }
}

// Main function
int main() {
    int size = 10; // Size of the hash table
    HashTable* table = createHashTable(size);

    insert(table, "apple", "red");
    insert(table, "banana", "yellow");
    insert(table, "orange", "orange");

    printHashTable(table);

    printf("Search for 'apple': %s\n", search(table, "apple"));
    printf("Search for 'grape': %s\n", search(table, "grape"));

    delete(table, "banana");

    printHashTable(table);

    return 0;
}