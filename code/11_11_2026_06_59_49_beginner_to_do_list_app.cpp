#include <iostream>
#include <string>
#include <vector>

using namespace std;

// To-do list item structure
struct TodoItem {
    string task;
    bool completed;
};

// Function to add a new to-do item
void addItem(vector<TodoItem>& todoList) {
    TodoItem newItem;
    cout << "Enter the task: ";
    getline(cin, newItem.task);
    newItem.completed = false;
    todoList.push_back(newItem);
}

// Function to display the to-do list
void displayTodoList(const vector<TodoItem>& todoList) {
    for (const auto& item : todoList) {
        cout << "Task: " << item.task;
        if (item.completed)
            cout << " [Completed]";
        else
            cout << " [Not completed]";
        cout << endl;
    }
}

// Function to complete a task
void completeTask(vector<TodoItem>& todoList) {
    string task;
    cout << "Enter the task to complete: ";
    getline(cin, task);
    for (auto& item : todoList) {
        if (item.task == task) {
            item.completed = true;
            return;
        }
    }
    cout << "Task not found!" << endl;
}

int main() {
    vector<TodoItem> todoList;

    while (true) {
        cout << "To-Do List App" << endl;
        cout << "1. Add task" << endl;
        cout << "2. Display tasks" << endl;
        cout << "3. Complete task" << endl;
        cout << "4. Quit" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addItem(todoList);
                break;
            case 2:
                displayTodoList(todoList);
                break;
            case 3:
                completeTask(todoList);
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again!" << endl;
        }
    }

    return 0;
}