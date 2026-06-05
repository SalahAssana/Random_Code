# To-Do List
# A simple program that allows users to add and remove tasks.

# Initialize an empty list to store tasks
tasks = []

def add_task(task):
    # Add a new task to the list
    tasks.append(task)

def remove_task(task):
    # Remove a task from the list if it exists
    if task in tasks:
        tasks.remove(task)

def print_tasks():
    # Print all tasks in the list
    for task in tasks:
        print(task)

if __name__ == '__main__':
    while True:
        # Display menu options
        print("1. Add Task")
        print("2. Remove Task")
        print("3. View Tasks")
        print("4. Quit")

        choice = input("Choose an option: ")

        if choice == "1":
            task = input("Enter a new task: ")
            add_task(task)
        elif choice == "2":
            task = input("Enter the task to remove: ")
            remove_task(task)
        elif choice == "3":
            print_tasks()
        elif choice == "4":
            break
        else:
            print("Invalid option. Please try again.")