Here is the C code for the project:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for an AST node
typedef struct {
    char *token;
    int lineNum;
    int colNum;
} Node;

// Define the structure for a symbol table entry
typedef struct {
    char *name;
    int type; // 0: integer, 1: floating-point number, 2: string
    Node *value;
} SymbolTableEntry;

// Define the structure for the symbol table
typedef struct {
    SymbolTableEntry **entries;
    int size;
    int capacity;
} SymbolTable;

// Function to create a new symbol table entry
SymbolTableEntry* createSymbolTableEntry(char *name, int type) {
    SymbolTableEntry* entry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    entry->name = name;
    entry->type = type;
    entry->value = NULL;
    return entry;
}

// Function to create a new symbol table
SymbolTable* createSymbolTable(int initialCapacity) {
    SymbolTable* table = (SymbolTable*)malloc(sizeof(SymbolTable));
    table->entries = (SymbolTableEntry**)malloc(initialCapacity * sizeof(SymbolTableEntry*));
    table->size = 0;
    table->capacity = initialCapacity;
    return table;
}

// Function to insert a new symbol table entry
void insertSymbolTableEntry(SymbolTable* table, char *name, int type) {
    if (table->size >= table->capacity) {
        // Reallocate memory for the entries array
        table->entries = (SymbolTableEntry**)realloc(table->entries, (table->capacity *= 2) * sizeof(SymbolTableEntry*));
    }
    SymbolTableEntry* entry = createSymbolTableEntry(name, type);
    table->entries[table->size++] = entry;
}

// Function to find a symbol table entry by name
SymbolTableEntry* findSymbolTableEntry(SymbolTable* table, char *name) {
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->entries[i]->name, name) == 0) {
            return table->entries[i];
        }
    }
    return NULL;
}

// Function to print the symbol table
void printSymbolTable(SymbolTable* table) {
    for (int i = 0; i < table->size; i++) {
        printf("%s: %d\n", table->entries[i]->name, table->entries[i]->type);
    }
}

// Main function
int main() {
    SymbolTable* table = createSymbolTable(10);

    insertSymbolTableEntry(table, "x", 0);
    insertSymbolTableEntry(table, "y", 1);
    insertSymbolTableEntry(table, "str", 2);

    printSymbolTable(table);

    return 0;
}
```