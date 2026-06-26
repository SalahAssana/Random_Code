# To-Do List App
# A simple, single-concept program that lets users create and manage their to-do lists.

# Import necessary modules
import os

# Initialize an empty list to store tasks
tasks = []

def add_task(task):
    # Add task to the tasks list
    tasks.append(task)
    print(f"Task '{task}' added!")

def view_tasks():
    # Print all tasks in the tasks list
    if len(tasks) == 0:
        print("No tasks available.")
    else:
        for i, task in enumerate(tasks, start=1):
            print(f"{i}. {task}")

def delete_task(task_index):
    try:
        # Remove task at given index from the tasks list
        del tasks[int(task_index)-1]
        print(f"Task '{task_index}' deleted!")
    except (IndexError, ValueError):
        print("Invalid task index!")

if __name__ == '__main__':
    while True:
        os.system('cls' if os.name == 'nt' else 'clear')  # Clear console
        print("To-Do List App")
        print("-----------------")
        print("1. Add Task")
        print("2. View Tasks")
        print("3. Delete Task")
        print("4. Quit")
        
        choice = input("Choose an option: ")
        
        if choice == "1":
            task = input("Enter a new task: ")
            add_task(task)
        elif choice == "2":
            view_tasks()
        elif choice == "3":
            task_index = input("Enter the task index to delete (1-based): ")
            delete_task(task_index)
        elif choice == "4":
            print("Goodbye!")
            break
        else: