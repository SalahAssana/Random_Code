# To-Do List Manager

# Dictionary to store tasks
tasks = {}

def add_task():
    task_name = input("Enter task name: ")
    if task_name in tasks:
        print("Task already exists!")
    else:
        tasks[task_name] = "Not completed"
        print(f"Task '{task_name}' added!")

def remove_task():
    task_name = input("Enter task name to remove: ")
    if task_name not in tasks:
        print("Task does not exist!")
    else:
        del tasks[task_name]
        print(f"Task '{task_name}' removed!")

def mark_completed():
    task_name = input("Enter task name to mark completed: ")
    if task_name not in tasks:
        print("Task does not exist!")
    else:
        tasks[task_name] = "Completed"
        print(f"Task '{task_name}' marked as completed!")

def display_tasks():
    for task, status in tasks.items():
        print(f"{task}: {status}")

if __name__ == '__main__':
    while True:
        print("\n1. Add Task\n2. Remove Task\n3. Mark Completed\n4. Display Tasks\n5. Quit")
        choice = input("Choose an option: ")
        if choice == "1":
            add_task()
        elif choice == "2":
            remove_task()
        elif choice == "3":
            mark_completed()
        elif choice == "4":
            display_tasks()
        elif choice == "5":
            break
        else:
            print("Invalid option! Try again.")