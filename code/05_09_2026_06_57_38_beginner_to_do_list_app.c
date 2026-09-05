#include <stdio.h>
#include <stdlib.h>

// Define structure for tasks
typedef struct {
    char* task;
    int completed;
} Task;

// Function to add a new task
void addTask(Task** tasks, int* numTasks) {
    (*numTasks)++;
    *tasks = (Task*) realloc(*tasks, sizeof(Task) * (*numTasks));
}

// Function to remove a task
void removeTask(Task** tasks, int* numTasks, char* taskName) {
    for (int i = 0; i < *numTasks; i++) {
        if (strcmp(tasks[i]->task, taskName) == 0) {
            for (int j = i; j < *numTasks - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            (*numTasks)--;
            return;
        }
    }
}

// Function to mark a task as completed
void completeTask(Task** tasks, int* numTasks, char* taskName) {
    for (int i = 0; i < *numTasks; i++) {
        if (strcmp(tasks[i]->task, taskName) == 0) {
            tasks[i]->completed = 1;
            return;
        }
    }
}

// Function to print the to-do list
void printTasks(Task** tasks, int numTasks) {
    for (int i = 0; i < numTasks; i++) {
        printf("%s", tasks[i]->task);
        if (tasks[i]->completed) {
            printf(" [COMPLETED]");
        }
        printf("\n");
    }
}

int main() {
    Task* tasks = NULL;
    int numTasks = 0;

    // Add some sample tasks
    addTask(&tasks, &numTasks);
    tasks[numTasks-1].task = (char*) malloc(strlen("Buy milk") + 1);
    strcpy(tasks[numTasks-1].task, "Buy milk");
    addTask(&tasks, &numTasks);
    tasks[numTasks-1].task = (char*) malloc(strlen("Walk the dog") + 1);
    strcpy(tasks[numTasks-1].task, "Walk the dog");

    // Print the initial to-do list
    printf("Initial To-Do List:\n");
    printTasks(&tasks, numTasks);

    // Remove a task
    removeTask(&tasks, &numTasks, "Buy milk");

    // Mark another task as completed
    completeTask(&tasks, &numTasks, "Walk the dog");

    // Print the updated to-do list
    printf("Updated To-Do List:\n");
    printTasks(&tasks, numTasks);

    for (int i = 0; i < numTasks; i++) {
        free(tasks[i].task);
    }
    free(tasks);

    return 0;
}