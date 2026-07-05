#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TodoList {
public:
    void addTask(string task) {
        tasks_.push_back(task);
    }

    void removeTask(int index) {
        if(index >= 0 && index < tasks_.size()) {
            tasks_.erase(tasks_.begin() + index);
        }
    }

    void listTasks() {
        for(int i = 0; i < tasks_.size(); i++) {
            cout << "Task " << (i+1) << ": " << tasks_[i] << endl;
        }
    }

private:
    vector<string> tasks_;
};

int main() {
    TodoList todo;
    int choice;

    while(true) {
        cout << "To-Do List App" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Remove Task" << endl;
        cout << "3. List Tasks" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                string task;
                cout << "Enter new task: ";
                getline(cin, task);
                todo.addTask(task);
                break;
            case 2:
                int index;
                cout << "Enter the task number to remove: ";
                cin >> index;
                todo.removeTask(index - 1);
                break;
            case 3:
                todo.listTasks();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}