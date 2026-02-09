#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a task
struct Task {
    string description;
    string dueDate;
};

// Function to add a new task
void addTask(vector<Task>& tasks, string description, string dueDate) {
    tasks.push_back({description, dueDate});
}

// Function to remove a task by description
void removeTask(vector<Task>& tasks, string description) {
    for (auto& task : tasks) {
        if (task.description == description) {
            tasks.erase(remove(tasks.begin(), tasks.end(), task), tasks.end());
            return;
        }
    }
}

// Function to list all tasks with due dates
void listTasks(const vector<Task>& tasks) {
    for (const auto& task : tasks) {
        cout << "Task: " << task.description << ", Due Date: " << task.dueDate << endl;
    }
}

int main() {
    vector<Task> tasks;

    while (true) {
        cout << "To-Do List App" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Remove Task" << endl;
        cout << "3. List Tasks" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                string description, dueDate;
                cout << "Enter task description: ";
                getline(cin, description);
                cout << "Enter due date (optional): ";
                getline(cin, dueDate);
                addTask(tasks, description, dueDate);
                break;
            case 2:
                string taskDescription;
                cout << "Enter task to remove: ";
                getline(cin, taskDescription);
                removeTask(tasks, taskDescription);
                break;
            case 3:
                listTasks(tasks);
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}