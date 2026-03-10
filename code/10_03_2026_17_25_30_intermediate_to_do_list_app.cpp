#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Struct to represent a task
struct Task {
    string name;
    bool isDone;
    int priority; // 1-5, with 1 being the lowest and 5 being the highest
};

// Function to add a new task to the list
void addTask(vector<Task>& tasks) {
    cout << "Enter the task name: ";
    string name;
    cin >> name;

    Task newTask = {name, false, 3}; // default priority is 3

    tasks.push_back(newTask);
    cout << "Task added successfully!" << endl;
}

// Function to remove a task from the list
void removeTask(vector<Task>& tasks) {
    cout << "Enter the name of the task to remove: ";
    string name;
    cin >> name;

    for (auto& task : tasks) {
        if (task.name == name) {
            tasks.erase(remove(tasks.begin(), tasks.end(), task), tasks.end());
            cout << "Task removed successfully!" << endl;
            return;
        }
    }

    cout << "Task not found." << endl;
}

// Function to prioritize a task
void priorityTask(vector<Task>& tasks) {
    cout << "Enter the name of the task to prioritize: ";
    string name;
    cin >> name;

    for (auto& task : tasks) {
        if (task.name == name) {
            int newPriority;
            cout << "Enter the new priority (1-5): ";
            cin >> newPriority;
            task.priority = newPriority;
            cout << "Task prioritized successfully!" << endl;
            return;
        }
    }

    cout << "Task not found." << endl;
}

// Function to display all tasks
void displayTasks(const vector<Task>& tasks) {
    for (const auto& task : tasks) {
        if (!task.isDone) {
            cout << "Task: " << task.name << ", Priority: " << task.priority << endl;
        }
    }
}

int main() {
    vector<Task> tasks;

    while (true) {
        cout << "1. Add Task" << endl;
        cout << "2. Remove Task" << endl;
        cout << "3. Prioritize Task" << endl;
        cout << "4. Display Tasks" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                removeTask(tasks);
                break;
            case 3:
                priorityTask(tasks);
                break;
            case 4:
                displayTasks(tasks);
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}