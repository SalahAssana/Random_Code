#include <iostream>
#include <string>
#include <vector>

using namespace std;

// To-do list class
class ToDoList {
public:
    vector<string> tasks;
    int completedCount = 0;

    // Add task
    void addTask(string task) {
        tasks.push_back(task);
    }

    // Remove task
    void removeTask(int index) {
        if (index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        }
    }

    // Mark task as completed
    void completeTask(int index) {
        if (index < tasks.size()) {
            tasks[index] += " [Completed]";
            completedCount++;
        }
    }

    // Display to-do list
    void displayList() {
        for (int i = 0; i < tasks.size(); i++) {
            cout << "[" << i << "] " << tasks[i] << endl;
        }
    }
};

int main() {
    ToDoList todolist;

    while (true) {
        cout << "To-Do List App" << endl;
        cout << "1. Add task" << endl;
        cout << "2. Remove task" << endl;
        cout << "3. Complete task" << endl;
        cout << "4. Display list" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                string task;
                cout << "Enter task: ";
                getline(cin, task);
                todolist.addTask(task);
                break;
            case 2:
                int index;
                cout << "Enter task index to remove: ";
                cin >> index;
                todolist.removeTask(index);
                break;
            case 3:
                int completeIndex;
                cout << "Enter task index to complete: ";
                cin >> completeIndex;
                todelist.completeTask(completeIndex);
                break;
            case 4:
                todolist.displayList();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}