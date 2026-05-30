# To-Do List Program

# Import necessary modules
import os

# Initialize an empty list to store tasks
tasks = []

def add_task():
    # Ask user for task name
    task_name = input("Enter a new task: ")
    
    # Add the task to the list
    tasks.append(task_name)
    
    # Print confirmation message
    print(f"Task '{task_name}' added!")

def remove_task():
    # Ask user for the index of the task to be removed
    index = int(input("Enter the index of the task to remove: "))
    
    # Check if the index is valid
    if 0 <= index < len(tasks):
        # Remove the task from the list
        del tasks[index]
        
        # Print confirmation message
        print(f"Task at index {index} removed!")
    else:
        print("Invalid index. Try again!")

def display_tasks():
    # Display all tasks in the list
    for i, task in enumerate(tasks):
        print(f"{i+1}. {task}")

if __name__ == '__main__':
    while True:
        # Print menu options
        print("\nTo-Do List Menu:")
        print("1. Add a new task")
        print("2. Remove a task")
        print("3. Display tasks")
        print("4. Quit")
        
        # Ask user for their choice
        choice = input("Enter your choice: ")
        
        if choice == "1":
            add_task()
        elif choice == "2":
            remove_task()
        elif choice == "3":
            display_tasks()
        elif choice == "4":
            print("Goodbye!")
            break
        else: