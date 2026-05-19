# To-Do List Program

# Importing necessary modules
import os

class ToDoList:
    def __init__(self):
        self.tasks = []

    def add_task(self, task):
        """Add a new task to the list"""
        self.tasks.append(task)

    def remove_task(self, task):
        """Remove a task from the list if it exists"""
        if task in self.tasks:
            self.tasks.remove(task)
        else:
            print("Task not found!")

    def display_tasks(self):
        """Display all tasks in the list"""
        for i, task in enumerate(self.tasks, start=1):
            print(f"{i}. {task}")

def main():
    todo_list = ToDoList()

    while True:
        os.system('cls' if os.name == 'nt' else 'clear')
        print("To-Do List Menu:")
        print("1. Add task")
        print("2. Remove task")
        print("3. Display tasks")
        print("4. Exit")

        choice = input("Enter your choice: ")

        if choice == "1":
            task = input("Enter the task: ")
            todo_list.add_task(task)
        elif choice == "2":
            task = input("Enter the task to remove: ")
            todo_list.remove_task(task)
        elif choice == "3":
            todo_list.display_tasks()
        elif choice == "4":
            break
        else:
            print("Invalid choice!")

if __name__ == '__main__':