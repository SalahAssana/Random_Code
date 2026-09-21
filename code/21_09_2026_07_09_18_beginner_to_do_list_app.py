# To-Do List App
# A simple program to manage tasks and deadlines.

to_do_list = []

def add_task(task_name):
    global to_do_list
    to_do_list.append({"task": task_name, "deadline": input("Enter deadline for this task: ")})

def view_tasks():
    global to_do_list
    if not to_do_list:
        print("No tasks in the list.")
    else:
        for task in to_do_list:
            print(f"Task: {task['task']}, Deadline: {task['deadline']}")

def main():
    while True:
        print("\nTo-Do List App")
        print("1. Add Task")
        print("2. View Tasks")
        print("3. Exit")
        
        choice = input("Choose an option: ")
        
        if choice == "1":
            task_name = input("Enter the name of your task: ")
            add_task(task_name)
        elif choice == "2":
            view_tasks()
        elif choice == "3":
            break
        else:
            print("Invalid choice. Please choose a valid option.")

if __name__ == '__main__':
    main()