#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a hash table entry
typedef struct {
    char *key;
    int value;
} HashEntry;

// Define the structure for the hash table
typedef struct {
    HashEntry **table; // Array of pointers to hash entries
    int size; // Size of the hash table
} HashTable;

// Function to create a new hash table with a given size
HashTable *create_hash_table(int size) {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->table = (HashEntry **)calloc(size, sizeof(HashEntry *));
    return table;
}

// Function to insert a new entry into the hash table
void insert_hash_entry(HashTable *table, char *key, int value) {
    int index = hash_function(key) % table->size; // Calculate the index for the key
    HashEntry *entry = (HashEntry *)malloc(sizeof(HashEntry));
    entry->key = strdup(key);
    entry->value = value;
    table->table[index] = entry; // Insert the new entry into the table
}

// Function to retrieve a value from the hash table
int get_hash_value(HashTable *table, char *key) {
    int index = hash_function(key) % table->size; // Calculate the index for the key
    HashEntry *entry = table->table[index];
    if (entry != NULL && strcmp(entry->key, key) == 0) {
        return entry->value;
    } else {
        return -1; // Key not found in the hash table
    }
}

// Function to perform a custom hash function
int hash_function(char *key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash += key[i];
    }
    return hash % 10; // Simple hash function that maps keys to indices in the table
}

// Function to print the contents of the hash table
void print_hash_table(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        HashEntry *entry = table->table[i];
        if (entry != NULL) {
            printf("Key: %s, Value: %d\n", entry->key, entry->value);
        }
    }
}

// Main function to test the hash table implementation
int main() {
    HashTable *table = create_hash_table(10); // Create a new hash table with size 10

    insert_hash_entry(table, "apple", 5);
    insert_hash_entry(table, "banana", 3);
    insert_hash_entry(table, "orange", 7);

    printf("Hash Table Contents:\n");
    print_hash_table(table);

    int value = get_hash_value(table, "banana");
    if (value != -1) {
        printf("Value for key 'banana' is: %d\n", value);
    } else {
        printf("Key 'banana' not found in the hash table.\n");
    }

    return 0;
}