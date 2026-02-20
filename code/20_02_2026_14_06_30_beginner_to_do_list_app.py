# To-Do List App

# Import necessary modules
import os
from datetime import date

# Define a class for tasks
class Task:
    def __init__(self, name):
        self.name = name
        self.completed = False

# Define the to-do list app class
class TodoListApp:
    def __init__(self):
        self.tasks = []

    # Method to add a task
    def add_task(self, name):
        new_task = Task(name)
        self.tasks.append(new_task)

    # Method to remove a task
    def remove_task(self, name):
        for task in self.tasks:
            if task.name == name:
                self.tasks.remove(task)
                return

    # Method to mark a task as completed
    def complete_task(self, name):
        for task in self.tasks:
            if task.name == name:
                task.completed = True
                return

    # Method to display the to-do list
    def show_tasks(self):
        print("To-Do List:")
        for i, task in enumerate(self.tasks):
            completed_str = "Completed" if task.completed else ""
            print(f"{i+1}. {task.name} - {completed_str}")

# Main function
if __name__ == '__main__':
    app = TodoListApp()

    while True:
        print("\nOptions:")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. Complete Task")
        print("4. Show Tasks")
        print("5. Exit")

        choice = input("Choose an option: ")

        if choice == "1":
            name = input("Enter task name: ")
            app.add_task(name)
        elif choice == "2":
            name = input("Enter task name to remove: ")
            app.remove_task(name)
        elif choice == "3":
            name = input("Enter task name to complete: ")
            app.complete_task(name)
        elif choice == "4":
            app.show_tasks()
        elif choice == "5":
            break
        else:
            print("Invalid option. Please choose again.")