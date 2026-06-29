#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Structure to hold task information
struct Task {
    string name;
    int deadline; // in days
};

// Binary Search Tree Node
struct TreeNode {
    Task data;
    TreeNode* left;
    TreeNode* right;
};

// Function to create a new tree node
TreeNode* newNode(Task data) {
    TreeNode* node = new TreeNode();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// Binary Search Tree class
class Bst {
public:
    TreeNode* root;

    // Function to insert a task into the tree
    void insert(Task task) {
        if (root == nullptr) {
            root = newNode(task);
        } else {
            insert(root, task);
        }
    }

private:
    void insert(TreeNode*& node, Task task) {
        if (task.deadline < node->data.deadline) {
            if (node->left == nullptr) {
                node->left = newNode(task);
            } else {
                insert(node->left, task);
            }
        } else {
            if (node->right == nullptr) {
                node->right = newNode(task);
            } else {
                insert(node->right, task);
            }
        }
    }

    // Function to print the tasks in the tree
    void printTasks() const {
        print(root);
    }

private:
    void print(TreeNode* node) const {
        if (node == nullptr) {
            return;
        }
        print(node->left);
        cout << "Task: " << node->data.name << ", Deadline: " << node->data.deadline << endl;
        print(node->right);
    }
};

int main() {
    Bst bst;

    // Create some sample tasks
    Task task1 = {"Task 1", 3};
    Task task2 = {"Task 2", 5};
    Task task3 = {"Task 3", 1};
    Task task4 = {"Task 4", 7};

    // Insert the tasks into the tree
    bst.insert(task1);
    bst.insert(task2);
    bst.insert(task3);
    bst.insert(task4);

    // Print the tasks in the tree
    cout << "Tasks:" << endl;
    bst.printTasks();

    return 0;
}