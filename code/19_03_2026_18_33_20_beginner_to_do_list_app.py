# To-Do List App

tasks = []

def add_task(task_name):
    """Add a new task to the list."""
    tasks.append({"name": task_name, "done": False})

def remove_task(index):
    """Remove a task from the list."""
    if index < len(tasks):
        del tasks[index]
    else:
        print("Invalid task index.")

def display_tasks():
    """Display all tasks in the list."""
    for i, task in enumerate(tasks):
        done = "*" if task["done"] else " "
        print(f"{i}. {task['name']} [{done}]")

def mark_done(index):
    """Mark a task as done."""
    if index < len(tasks):
        tasks[index]["done"] = True
    else:
        print("Invalid task index.")

if __name__ == '__main__':
    while True:
        print("\nTo-Do List App")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. Display Tasks")
        print("4. Mark Done")
        print("5. Quit")
        
        choice = input("Choose an option: ")
        
        if choice == "1":
            task_name = input("Enter a new task name: ")
            add_task(task_name)
        elif choice == "2":
            index = int(input("Enter the task index to remove: "))
            remove_task(index)
        elif choice == "3":
            display_tasks()
        elif choice == "4":
            index = int(input("Enter the task index to mark done: "))
            mark_done(index)
        elif choice == "5":
            break
        else:
            print("Invalid option. Try again!")