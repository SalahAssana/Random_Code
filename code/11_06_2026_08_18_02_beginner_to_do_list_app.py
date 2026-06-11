# To-Do List App

tasks = []

def add_task():
    task = input("Enter your new task: ")
    tasks.append(task)
    print(f"Task '{task}' added!")

def remove_task():
    if len(tasks) > 0:
        task_index = int(input("Enter the task number to remove (1-based): "))
        if task_index <= len(tasks):
            del tasks[task_index - 1]
            print(f"Task {task_index} removed!")
        else:
            print("Invalid task number.")
    else:
        print("No tasks to remove.")

def display_tasks():
    for i, task in enumerate(tasks, start=1):
        print(f"{i}. {task}")

if __name__ == '__main__':
    while True:
        print("\nTo-Do List App")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. Display Tasks")
        print("4. Quit")
        
        choice = input("Enter your choice: ")
        
        if choice == "1":
            add_task()
        elif choice == "2":
            remove_task()
        elif choice == "3":
            display_tasks()
        elif choice == "4":
            break
        else:
            print("Invalid choice. Please try again.")