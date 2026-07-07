# To-Do List App
# BEGINNER complexity project

tasks = []  # list to store tasks

def add_task(task):
    """Add a new task"""
    global tasks
    tasks.append({"task": task, "completed": False})

def remove_task(index):
    """Remove a task by index"""
    global tasks
    if index < len(tasks):
        del tasks[index]
    else:
        print("Invalid task index")

def mark_completed(index):
    """Mark a task as completed by index"""
    global tasks
    if index < len(tasks):
        tasks[index]["completed"] = True
    else:
        print("Invalid task index")

def display_tasks():
    """Display all tasks with completion status"""
    global tasks
    for i, task in enumerate(tasks):
        status = "Completed" if task["completed"] else "Not completed"
        print(f"{i+1}. {task['task']} - {status}")

if __name__ == '__main__':
    while True:
        print("1. Add task")
        print("2. Remove task")
        print("3. Mark task as completed")
        print("4. Display tasks")
        print("5. Quit")
        
        choice = input("Choose an option: ")
        
        if choice == "1":
            task = input("Enter task: ")
            add_task(task)
        elif choice == "2":
            index = int(input("Enter task index to remove: "))
            remove_task(index-1)  # subtract 1 because list indices start at 0
        elif choice == "3":
            index = int(input("Enter task index to mark as completed: "))
            mark_completed(index-1)
        elif choice == "4":
            display_tasks()
        elif choice == "5":
            break
        else: