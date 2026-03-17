#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Task {
    std::string name;
    int priority;
    int dueDate;
};

// Custom sorting algorithm for tasks
bool compareTasks(const Task& a, const Task& b) {
    // Priority first
    if (a.priority != b.priority) {
        return a.priority > b.priority;
    }
    // Then by due date
    else {
        return a.dueDate > b.dueDate;
    }
}

int main() {
    std::vector<Task> tasks = {
        {"Task A", 1, 1},
        {"Task B", 2, 3},
        {"Task C", 1, 2},
        {"Task D", 3, 4},
        {"Task E", 2, 5}
    };

    // Sort tasks
    std::sort(tasks.begin(), tasks.end(), compareTasks);

    // Print sorted tasks
    for (const auto& task : tasks) {
        std::cout << "Name: " << task.name << ", Priority: " << task.priority
                  << ", Due Date: " << task.dueDate << std::endl;
    }

    return 0;
}