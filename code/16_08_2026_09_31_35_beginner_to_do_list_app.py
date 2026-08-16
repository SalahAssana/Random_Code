# To-Do List App
tasks = []

def add_task():
    task = input("Enter your to-do task: ")
    tasks.append(task)
    print(f"Task '{task}' added successfully!")

def remove_task():
    if len(tasks) > 0:
        task_index = int(input("Enter the task number to remove (1-based): "))
        try:
            del tasks[task_index - 1]
            print("Task removed successfully!")
        except IndexError:
            print("Invalid task index. Try again.")
    else:
        print("No tasks available for removal.")

def display_tasks():
    if len(tasks) > 0:
        print("Your to-do list:")
        for i, task in enumerate(tasks, start=1):
            print(f"{i}. {task}")
    else:
        print("No tasks available.")

if __name__ == '__main__':
    while True:
        print("\nTo-Do List App")
        print("1. Add a task")
        print("2. Remove a task")
        print("3. Display tasks")
        print("4. Quit")
        
        choice = input("Enter your choice (1/2/3/4): ")
        
        if choice == '1':
            add_task()
        elif choice == '2':
            remove_task()
        elif choice == '3':
            display_tasks()
        elif choice == '4':
            print("Goodbye!")
            break
        else:
            print("Invalid choice. Try again.")