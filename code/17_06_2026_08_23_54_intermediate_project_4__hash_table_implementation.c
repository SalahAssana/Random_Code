#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 256
#define MAX_KEY_LENGTH 10
#define MAX_VALUE_LENGTH 20

typedef struct {
    char key[MAX_KEY_LENGTH];
    int value;
} Entry;

typedef struct {
    Entry* table[TABLE_SIZE];
} HashTable;

HashTable* create_hash_table() {
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    for(int i=0; i<TABLE_SIZE; i++) {
        table->table[i] = NULL;
    }
    return table;
}

int hash_function(const char* key) {
    int hash = 0;
    for(int i=0; i<strlen(key); i++) {
        hash += (int)key[i];
    }
    return hash % TABLE_SIZE;
}

void insert(HashTable* table, const char* key, int value) {
    int index = hash_function(key);
    Entry* entry = (Entry*) malloc(sizeof(Entry));
    strcpy(entry->key, key);
    entry->value = value;
    if(table->table[index] == NULL) {
        table->table[index] = entry;
    } else {
        // collision resolution strategy: linear probing
        int i=1;
        while(table->table[(index+i)%TABLE_SIZE] != NULL) {
            i++;
        }
        table->table[(index+i)%TABLE_SIZE] = entry;
    }
}

int get(HashTable* table, const char* key) {
    int index = hash_function(key);
    for(int i=0; table->table[index] != NULL; i++) {
        if(strcmp(table->table[index]->key, key) == 0) {
            return table->table[index]->value;
        }
        index = (index + i + 1) % TABLE_SIZE;
    }
    return -1; // not found
}

void print_hash_table(HashTable* table) {
    for(int i=0; i<TABLE_SIZE; i++) {
        if(table->table[i] != NULL) {
            printf("%s: %d\n", table->table[i]->key, table->table[i]->value);
        }
    }
}

int main() {
    HashTable* table = create_hash_table();
    
    insert(table, "apple", 1);
    insert(table, "banana", 2);
    insert(table, "orange", 3);
    
    printf("Hash Table:\n");
    print_hash_table(table);
    
    printf("Value of apple: %d\n", get(table, "apple"));
    printf("Value of banana: %d\n", get(table, "banana"));
    printf("Value of orange: %d\n", get(table, "orange"));
    
    return 0;
}