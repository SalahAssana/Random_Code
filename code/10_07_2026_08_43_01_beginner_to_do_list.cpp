#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TodoList {
public:
    vector<string> tasks;
    
    void addTask(string task) {
        tasks.push_back(task);
    }
    
    void removeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        } else {
            cout << "Invalid index. Task not removed." << endl;
        }
    }
    
    void displayTasks() {
        for (int i = 0; i < tasks.size(); i++) {
            cout << "Task " << i + 1 << ": " << tasks[i] << endl;
        }
    }
};

int main() {
    TodoList todoList;

    while (true) {
        cout << "1. Add task" << endl;
        cout << "2. Remove task" << endl;
        cout << "3. Display tasks" << endl;
        cout << "4. Exit" << endl;
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                string task;
                cout << "Enter a new task: ";
                getline(cin, task);
                todoList.addTask(task);
                break;
            case 2:
                int index;
                cout << "Enter the index of the task to remove: ";
                cin >> index;
                todoList.removeTask(index - 1);
                break;
            case 3:
                todoList.displayTasks();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}