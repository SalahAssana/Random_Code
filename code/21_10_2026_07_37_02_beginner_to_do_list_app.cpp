#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TodoList {
public:
    void addTask(string task) {
        tasks.push_back(task);
    }

    void removeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        }
    }

    void listTasks() {
        for (int i = 0; i < tasks.size(); i++) {
            cout << "Task " << i + 1 << ": " << tasks[i] << endl;
        }
    }

private:
    vector<string> tasks;
};

int main() {
    TodoList todo;

    // Add some tasks
    todo.addTask("Buy milk");
    todo.addTask("Walk the dog");
    todo.addTask("Do laundry");

    // List all tasks
    cout << "All tasks:" << endl;
    todo.listTasks();

    // Remove a task
    todo.removeTask(1);

    // List all tasks again
    cout << "After removing one task:" << endl;
    todo.listTasks();

    return 0;
}