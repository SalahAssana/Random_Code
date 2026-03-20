# To-Do List App
tasks = []

def add_task(task_name):
    tasks.append({"name": task_name, "completed": False})

def remove_task(index):
    if index >= len(tasks):
        print("Invalid task index!")
    else:
        del tasks[index]

def mark_completed(index):
    if index >= len(tasks):
        print("Invalid task index!")
    else:
        tasks[index]["completed"] = True

def list_tasks():
    for i, task in enumerate(tasks):
        status = "Completed" if task["completed"] else "Not Completed"
        print(f"{i+1}. {task['name']} - {status}")

if __name__ == '__main__':
    while True:
        print("\nTo-Do List App")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. Mark Task as Completed")
        print("4. List Tasks")
        print("5. Exit")
        
        choice = input("Choose an option: ")
        
        if choice == "1":
            task_name = input("Enter task name: ")
            add_task(task_name)
        elif choice == "2":
            index = int(input("Enter task index to remove: "))
            remove_task(index - 1)
        elif choice == "3":
            index = int(input("Enter task index to mark as completed: "))
            mark_completed(index - 1)
        elif choice == "4":
            list_tasks()
        elif choice == "5":
            break
        else:
            print("Invalid option. Please choose again.")