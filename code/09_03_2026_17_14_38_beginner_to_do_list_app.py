# To-Do List App
tasks = []

def add_task(task):
    global tasks
    tasks.append(task)
    print(f"Task '{task}' added!")

def remove_task(task):
    global tasks
    if task in tasks:
        tasks.remove(task)
        print(f"Task '{task}' removed!")
    else:
        print("Task not found.")

def display_tasks():
    global tasks
    print("Current Tasks:")
    for i, task in enumerate(tasks, start=1):
        print(f"{i}. {task}")

if __name__ == '__main__':
    while True:
        print("\nTo-Do List App")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. Display Tasks")
        print("4. Quit")

        choice = input("Choose an option (1/2/3/4): ")

        if choice == "1":
            task = input("Enter new task: ")
            add_task(task)
        elif choice == "2":
            task = input("Enter task to remove: ")
            remove_task(task)
        elif choice == "3":
            display_tasks()
        elif choice == "4":
            print("Goodbye!")
            break
        else:
            print("Invalid option. Try again.")