# To-Do List Program
# A simple program that allows users to add and remove tasks from a list.

tasks = []  # Initialize an empty list for tasks

def add_task(task):
    """Add a new task to the list."""
    tasks.append(task)
    print(f"Task '{task}' added.")

def remove_task(task):
    """Remove a task from the list if it exists."""
    if task in tasks:
        tasks.remove(task)
        print(f"Task '{task}' removed.")
    else:
        print("Task not found.")

def show_tasks():
    """Show all tasks in the list."""
    print("To-Do List:")
    for task in tasks:
        print(task)

if __name__ == '__main__':
    while True:
        print("\nOptions:\na) Add task\nr) Remove task\ns) Show tasks\ne) Exit")
        choice = input("Choose an option: ")
        
        if choice.lower() == 'a':
            task = input("Enter a new task: ")
            add_task(task)
        elif choice.lower() == 'r':
            task = input("Enter the task to remove: ")
            remove_task(task)
        elif choice.lower() == 's':
            show_tasks()
        elif choice.lower() == 'e':
            break
        else:
            print("Invalid option. Please choose again.")