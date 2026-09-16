# To-Do List App
# By [Your Name]

import os

class ToDoList:
    def __init__(self):
        self.tasks = {}

    def add_task(self, task_id, description):
        """Add a new task to the list"""
        if task_id in self.tasks:
            print("Task ID already exists. Please choose another one.")
            return
        self.tasks[task_id] = {"description": description, "done": False}

    def remove_task(self, task_id):
        """Remove a task from the list"""
        if task_id not in self.tasks:
            print("Task ID does not exist. Please check the IDs again.")
            return
        del self.tasks[task_id]

    def update_task(self, task_id, description=None, done=False):
        """Update an existing task"""
        if task_id not in self.tasks:
            print("Task ID does not exist. Please check the IDs again.")
            return
        if description:
            self.tasks[task_id]["description"] = description
        if done:
            self.tasks[task_id]["done"] = done

    def view_tasks(self):
        """View all tasks"""
        for task_id, task in self.tasks.items():
            print(f"Task ID: {task_id}, Description: {task['description']}, Done: {task['done']}")

def main():
    todo_list = ToDoList()

    while True:
        print("\n1. Add Task\n2. Remove Task\n3. Update Task\n4. View Tasks\n5. Exit")
        choice = input("Choose an option: ")

        if choice == "1":
            task_id = input("Enter the task ID: ")
            description = input("Enter the task description: ")
            todo_list.add_task(task_id, description)
        elif choice == "2":
            task_id = input("Enter the task ID to remove: ")
            todo_list.remove_task(task_id)
        elif choice == "3":
            task_id = input("Enter the task ID to update: ")
            description = input("Enter the new description (optional): ")
            done = input("Mark as done? (yes/no) ").lower() == "yes"
            todo_list.update_task(task_id, description, done)
        elif choice == "4":
            todo_list.view_tasks()
        elif choice == "5":
            print("Exiting...")
            break
        else:
            print("Invalid option. Please choose again.")

if __name__ == '__main__':