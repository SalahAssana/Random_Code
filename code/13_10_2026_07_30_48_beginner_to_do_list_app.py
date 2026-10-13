# To-Do List App

tasks = []

def add_task():
    task = input("Enter a new task: ")
    tasks.append(task)
    print(f"Task '{task}' added!")

def remove_task():
    if len(tasks) > 0:
        task_index = int(input("Enter the number of the task to remove (1-based): "))
        try:
            del tasks[task_index - 1]
            print(f"Task removed!")
        except IndexError:
            print("Invalid task number. Task not removed.")
    else:
        print("No tasks to remove.")

def list_tasks():
    if len(tasks) > 0:
        for i, task in enumerate(tasks, start=1):
            print(f"{i}. {task}")
    else:
        print("No tasks available.")

if __name__ == '__main__':
    while True:
        print("\nTo-Do List App")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. List Tasks")
        print("4. Quit")
        
        choice = input("Choose an option (1/2/3/4): ")
        
        if choice == '1':
            add_task()
        elif choice == '2':
            remove_task()
        elif choice == '3':
            list_tasks()
        elif choice == '4':
            print("Goodbye!")
            break
        else:
            print("Invalid option. Please try again.")