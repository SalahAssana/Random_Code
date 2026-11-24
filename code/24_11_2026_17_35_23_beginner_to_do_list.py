# To-Do List program in Python

to_do_list = []

def add_task(task):
    """Add a task to the list"""
    global to_do_list
    to_do_list.append(task)

def remove_task(index):
    """Remove a task from the list by index"""
    global to_do_list
    if 0 <= index < len(to_do_list):
        del to_do_list[index]
    else:
        print("Invalid index")

def display_tasks():
    """Display all tasks in the list"""
    global to_do_list
    for i, task in enumerate(to_do_list, start=1):
        print(f"{i}. {task}")

if __name__ == '__main__':
    while True:
        print("\nTo-Do List Menu:")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. Display Tasks")
        print("4. Quit")
        
        choice = input("Enter your choice: ")
        
        if choice == '1':
            task = input("Enter a new task: ")
            add_task(task)
        elif choice == '2':
            index = int(input("Enter the task number to remove: "))
            remove_task(index - 1)
        elif choice == '3':
            display_tasks()
        elif choice == '4':
            break
        else:
            print("Invalid choice. Please try again.")