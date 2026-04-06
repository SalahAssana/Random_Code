# To-Do List Program - Beginner Level Implementation

to_do_list = []

def add_task(task):
    """Add a task to the list"""
    global to_do_list
    to_do_list.append(task)
    print(f"Task '{task}' added!")

def remove_task(task):
    """Remove a task from the list"""
    global to_do_list
    if task in to_do_list:
        to_do_list.remove(task)
        print(f"Task '{task}' removed!")
    else:
        print("Task not found!")

def display_tasks():
    """Display all tasks in the list"""
    global to_do_list
    print("To-Do List:")
    for task in to_do_list:
        print(task)

if __name__ == '__main__':
    while True:
        print("\n1. Add Task\n2. Remove Task\n3. Display Tasks\n4. Quit")
        choice = input("Choose an option: ")
        
        if choice == '1':
            task = input("Enter a new task: ")
            add_task(task)
        elif choice == '2':
            task = input("Enter the task to remove: ")
            remove_task(task)
        elif choice == '3':
            display_tasks()
        elif choice == '4':
            print("Goodbye!")
            break
        else:
            print("Invalid option. Please choose again.")