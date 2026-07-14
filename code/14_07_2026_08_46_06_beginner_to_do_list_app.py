# To-Do List App

to_do_list = []

def add_task(task):
    global to_do_list
    to_do_list.append(task)
    print(f"Task '{task}' added.")

def remove_task(task):
    global to_do_list
    if task in to_do_list:
        to_do_list.remove(task)
        print(f"Task '{task}' removed.")
    else:
        print("Task not found.")

def display_tasks():
    global to_do_list
    if not to_do_list:
        print("No tasks available.")
    else:
        for i, task in enumerate(to_do_list):
            print(f"{i+1}. {task}")

if __name__ == '__main__':
    while True:
        print("\nTo-Do List App")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. Display Tasks")
        print("4. Quit")
        
        choice = input("Choose an option: ")
        
        if choice == "1":
            task = input("Enter a new task: ")
            add_task(task)
        elif choice == "2":
            task = input("Enter the task to remove: ")
            remove_task(task)
        elif choice == "3":
            display_tasks()
        elif choice == "4":
            print("Goodbye!")
            break
        else:
            print("Invalid option. Please try again.")