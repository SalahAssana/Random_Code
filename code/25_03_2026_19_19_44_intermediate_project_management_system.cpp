#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Project data structure
struct Project {
    string name;
    vector<Task> tasks; // list of tasks in the project
};

// Task data structure
struct Task {
    string description;
    int deadline; // deadline in days
    bool completed; // task completion status
};

// Function to add a new task to a project
void addTask(Project& project, const Task& task) {
    project.tasks.push_back(task);
}

// Function to check if a task is completed on or before the deadline
bool isTaskCompleted(const Task& task) {
    return task.completed || task.deadline < 0;
}

// Function to update the status of all tasks in a project
void updateTasks(Project& project, int daysPassed) {
    for (auto& task : project.tasks) {
        if (!task.completed && task.deadline > 0) {
            task.deadline -= daysPassed;
        }
        task.completed = task.deadline <= 0;
    }
}

// Function to print the status of all tasks in a project
void printTasks(const Project& project) {
    for (const auto& task : project.tasks) {
        cout << "Task: " << task.description << ", Deadline: ";
        if (task.completed) {
            cout << "Completed";
        } else if (task.deadline > 0) {
            cout << "Deadline in " << task.deadline << " days";
        } else {
            cout << "Overdue";
        }
        cout << endl;
    }
}

int main() {
    // Create a project with some tasks
    Project project1 = {"Project A", {}};
    addTask(project1, {"Task 1: Description 1", 3, false});
    addTask(project1, {"Task 2: Description 2", 5, false});
    addTask(project1, {"Task 3: Description 3", -1, true});

    // Update the tasks after some days have passed
    int daysPassed = 2;
    updateTasks(project1, daysPassed);

    // Print the status of all tasks in the project
    cout << "Project Status:" << endl;
    printTasks(project1);

    return 0;
}