#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ToDoList {
public:
    void addTask(string task) {
        tasks.push_back(task);
    }

    void removeTask(int index) {
        if(index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        } else {
            cout << "Invalid index. Task not removed." << endl;
        }
    }

    void listTasks() {
        for(int i = 0; i < tasks.size(); i++) {
            cout << "[" << i << "] " << tasks[i] << endl;
        }
    }

private:
    vector<string> tasks;
};

int main() {
    ToDoList todo;

    while(true) {
        cout << "To-Do List App" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Remove Task" << endl;
        cout << "3. List Tasks" << endl;
        cout << "4. Quit" << endl;

        int choice;
        cin >> choice;

        switch(choice) {
            case 1:
                string task;
                cout << "Enter a new task: ";
                cin.ignore();
                getline(cin, task);
                todo.addTask(task);
                break;
            case 2:
                int index;
                cout << "Enter the task number to remove: ";
                cin >> index;
                todo.removeTask(index);
                break;
            case 3:
                todo.listTasks();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}