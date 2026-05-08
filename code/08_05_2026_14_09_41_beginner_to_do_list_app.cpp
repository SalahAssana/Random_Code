#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TodoList {
public:
    void addItem(string task) {
        tasks.push_back(task);
    }

    void removeItem(int index) {
        if(index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        }
    }

    void viewTasks() {
        for(int i = 0; i < tasks.size(); i++) {
            cout << "Task " << (i+1) << ": " << tasks[i] << endl;
        }
    }

private:
    vector<string> tasks;
};

int main() {
    TodoList todo;

    while(true) {
        cout << "To-Do List App" << endl;
        cout << "1. Add task" << endl;
        cout << "2. Remove task" << endl;
        cout << "3. View tasks" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cin >> choice;

        switch(choice) {
            case 1:
                string task;
                cout << "Enter new task: ";
                getline(cin, task);
                todo.addItem(task);
                break;
            case 2:
                int index;
                cout << "Enter task number to remove (0-" << todo.tasks.size() - 1 << "): ";
                cin >> index;
                todo.removeItem(index);
                break;
            case 3:
                todo.viewTasks();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}