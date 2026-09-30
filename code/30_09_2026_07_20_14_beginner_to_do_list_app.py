# To-Do List App
tasks = []

def add_task():
    task = input("Enter new task: ")
    tasks.append(task)

def remove_task():
    if len(tasks) > 0:
        task_to_remove = input("Enter task to remove: ")
        if task_to_remove in tasks:
            tasks.remove(task_to_remove)
            print(f"Task '{task_to_remove}' removed.")
        else:
            print("Task not found. Nothing changed.")
    else:
        print("No tasks available.")

def list_tasks():
    if len(tasks) > 0:
        for i, task in enumerate(tasks):
            print(f"{i+1}. {task}")
    else:
        print("No tasks available.")

if __name__ == '__main__':
    while True:
        print("\nTo-Do List App\n")
        print("A) Add task")
        print("R) Remove task")
        print("L) List tasks")
        print("Q) Quit")
        
        choice = input("Choose an option: ").upper()
        
        if choice == 'A':
            add_task()
        elif choice == 'R':
            remove_task()
        elif choice == 'L':
            list_tasks()
        elif choice == 'Q':
            break
        else:
            print("Invalid choice. Try again.")