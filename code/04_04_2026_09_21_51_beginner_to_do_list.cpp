#include <iostream>
#include <string>
#include <vector>

using namespace std;

// A simple to-do list class
class TodoList {
public:
    // Add a task to the list
    void addTask(string task) {
        tasks.push_back(task);
    }

    // Remove a task from the list
    void removeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        }
    }

    // Print all tasks in the list
    void printTasks() {
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

    // Print all tasks
    todo.printTasks();

    // Remove a task
    todo.removeTask(1);

    // Print all tasks again
    todo.printTasks();

    return 0;
}