# To-Do List Organizer
# A simple program to organize and manage a to-do list using Python basics.

to_do_list = []

def add_task(task):
    """Add a new task to the to-do list."""
    global to_do_list
    to_do_list.append(task)
    print(f"Task '{task}' added!")

def view_tasks():
    """View all tasks in the to-do list."""
    if not to_do_list:
        print("No tasks available.")
    else:
        print("To-Do List:")
        for task in to_do_list:
            print(task)

def main():
    while True:
        print("\n1. Add Task")
        print("2. View Tasks")
        print("3. Exit")
        
        choice = input("Choose an option: ")
        
        if choice == "1":
            task = input("Enter a new task: ")
            add_task(task)
        elif choice == "2":
            view_tasks()
        elif choice == "3":
            break
        else:
            print("Invalid choice. Please choose again.")

if __name__ == '__main__':
    main()