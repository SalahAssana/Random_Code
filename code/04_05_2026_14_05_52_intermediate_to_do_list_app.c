#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for Task
typedef struct {
    char* description;
    int completed;
} Task;

// Define the structure for ToDoList
typedef struct {
    Task* tasks;
    int size;
} ToDoList;

// Function to create a new ToDoList
ToDoList* createToDoList(int capacity) {
    ToDoList* list = (ToDoList*)malloc(sizeof(ToDoList));
    list->tasks = (Task*)calloc(capacity, sizeof(Task));
    list->size = 0;
    return list;
}

// Function to add a task to the ToDoList
void addTask(ToDoList* list, char* description) {
    if (list->size >= list->tasks->description) {
        // Resize the array if necessary
        Task* newTasks = (Task*)realloc(list->tasks, sizeof(Task) * 2 * (list->size + 1));
        list->tasks = newTasks;
    }
    list->tasks[list->size].description = (char*)malloc(strlen(description) + 1);
    strcpy(list->tasks[list->size].description, description);
    list->tasks[list->size].completed = 0;
    list->size++;
}

// Function to print the ToDoList
void printToDoList(ToDoList* list) {
    for (int i = 0; i < list->size; i++) {
        printf("Task %d: %s\n", i + 1, list->tasks[i].description);
    }
}

// Function to delete a task from the ToDoList
void deleteTask(ToDoList* list, int index) {
    if (index >= list->size) {
        printf("Error: Task not found.\n");
        return;
    }
    free(list->tasks[index].description);
    for (int i = index; i < list->size - 1; i++) {
        list->tasks[i] = list->tasks[i + 1];
    }
    list->size--;
}

// Function to check if a task is completed
void markTaskCompleted(ToDoList* list, int index) {
    if (index >= list->size) {
        printf("Error: Task not found.\n");
        return;
    }
    list->tasks[index].completed = 1;
}

int main() {
    ToDoList* toDoList = createToDoList(5);
    
    addTask(toDoList, "Buy milk");
    addTask(toDoList, "Walk the dog");
    addTask(toDoList, "Clean the house");
    
    printToDoList(toDoList);
    
    markTaskCompleted(toDoList, 1);
    
    printToDoList(toDoList);
    
    deleteTask(toDoList, 2);
    
    printToDoList(toDoList);
    
    return 0;
}