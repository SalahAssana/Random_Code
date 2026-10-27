# To-do List App
# BEGINNER Complexity Level

tasks = []

def add_task():
    task = input("Enter new task: ")
    tasks.append({"task": task, "completed": False})

def remove_task():
    if len(tasks) > 0:
        task_index = int(input("Enter the index of the task to remove (or -1 to cancel): "))
        if task_index == -1:
            return
        try:
            del tasks[task_index]
        except IndexError:
            print("Invalid index. Task not removed.")
    else:
        print("No tasks available for removal.")

def mark_completed():
    if len(tasks) > 0:
        task_index = int(input("Enter the index of the task to mark as completed (or -1 to cancel): "))
        if task_index == -1:
            return
        try:
            tasks[task_index]["completed"] = True
        except IndexError:
            print("Invalid index. Task not marked as completed.")
    else:
        print("No tasks available for marking as completed.")

def display_tasks():
    for i, task in enumerate(tasks):
        status = "Completed" if task["completed"] else "Not Completed"
        print(f"{i}. {task['task']} ({status})")

if __name__ == '__main__':
    while True:
        print("\nTo-do List App")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. Mark as Completed")
        print("4. Display Tasks")
        print("5. Quit")
        choice = input("Enter your choice: ")
        
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
            print("Invalid choice. Please try again.")