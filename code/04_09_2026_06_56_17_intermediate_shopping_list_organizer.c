#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to represent an item on the shopping list
typedef struct {
    char *name;
    int quantity;
} Item;

// Function to add an item to the shopping list
void addItem(Item **list, int *size, char *name) {
    // Dynamically allocate memory for the new item
    Item *newItem = (Item *)malloc(sizeof(Item));
    newItem->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newItem->name, name);
    newItem->quantity = 0;

    // Add the new item to the list and increment the size
    (*list)[*size] = newItem;
    (*size)++;
}

// Function to remove an item from the shopping list
void removeItem(Item **list, int *size, char *name) {
    for (int i = 0; i < *size; i++) {
        if (strcmp(list[i]->name, name) == 0) {
            // Shift all items down one position to fill the gap
            for (int j = i + 1; j < *size; j++) {
                list[j - 1] = list[j];
            }
            // Decrement the size and free the removed item
            (*size]--;
            free(list[*size]->name);
            free(list[*size]);
            break;
        }
    }
}

// Function to update the quantity of an item on the shopping list
void updateQuantity(Item **list, int *size, char *name, int quantity) {
    for (int i = 0; i < *size; i++) {
        if (strcmp(list[i]->name, name) == 0) {
            list[i]->quantity = quantity;
            break;
        }
    }
}

// Function to print the shopping list
void printList(Item **list, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s: %d\n", list[i]->name, list[i]->quantity);
    }
}

// Main function
int main() {
    // Initialize the shopping list and its size
    Item *list = NULL;
    int size = 0;

    // Add items to the shopping list
    addItem(&list, &size, "Milk");
    addItem(&list, &size, "Bread");
    addItem(&list, &size, "Eggs");

    // Update the quantity of an item
    updateQuantity(&list, &size, "Milk", 2);

    // Remove an item from the shopping list
    removeItem(&list, &size, "Eggs");

    // Print the shopping list
    printList(&list, size);

    // Free dynamically allocated memory
    for (int i = 0; i < size; i++) {
        free(list[i]->name);
        free(list[i]);
    }
    free(list);

    return 0;
}