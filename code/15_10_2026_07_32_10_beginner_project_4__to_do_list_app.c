#include <stdio.h>
#include <stdlib.h>

// Define a struct to represent a task
typedef struct {
    char *title;
    int completed;
} Task;

// Function to add a new task
void addTask(Task **tasks, int *taskCount) {
    (*taskCount)++;
    (*tasks) = (Task *) realloc((*tasks), (*taskCount) * sizeof(Task));
}

// Function to remove a task
void removeTask(Task **tasks, int *taskCount, char *title) {
    for (int i = 0; i < *taskCount; i++) {
        if (strcmp((*tasks)[i].title, title) == 0) {
            Task *newTasks = (Task *) malloc(((*taskCount) - 1) * sizeof(Task));
            int j;
            for (j = 0; j < i; j++) {
                newTasks[j] = (*tasks)[j];
            }
            for (; j < *taskCount - 1; j++) {
                newTasks[j] = (*tasks)[j + 1];
            }
            free(*tasks);
            *tasks = newTasks;
            (*taskCount)--;
            return;
        }
    }
}

// Function to print the tasks
void printTasks(Task **tasks, int taskCount) {
    for (int i = 0; i < taskCount; i++) {
        printf("Task: %s, Completed: %d\n", (*tasks)[i].title, (*tasks)[i].completed);
    }
}

int main() {
    // Initialize the tasks array and count
    Task *tasks = NULL;
    int taskCount = 0;

    // Add some initial tasks
    addTask(&tasks, &taskCount);
    tasks[0].title = "Buy milk";
    tasks[0].completed = 0;
    addTask(&tasks, &taskCount);
    tasks[1].title = "Walk the dog";
    tasks[1].completed = 0;

    // Print the initial tasks
    printf("Initial Tasks:\n");
    printTasks(&tasks, taskCount);

    // Add a new task
    addTask(&tasks, &taskCount);
    tasks[2].title = "Do laundry";
    tasks[2].completed = 0;

    // Remove a task
    removeTask(&tasks, &taskCount, "Walk the dog");

    // Print the updated tasks
    printf("Updated Tasks:\n");
    printTasks(&tasks, taskCount);

    // Free the memory
    free(tasks);

    return 0;
}