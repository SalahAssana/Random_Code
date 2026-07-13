# To-Do List App
# A simple command-line app for managing tasks
# Beginner-level Python implementation

to_do_list = []

def add_task():
    task = input("Enter a new task: ")
    to_do_list.append(task)
    print(f"Task '{task}' added!")

def view_tasks():
    if not to_do_list:
        print("No tasks yet!")
    else:
        for i, task in enumerate(to_do_list, start=1):
            print(f"{i}. {task}")

def main():
    while True:
        print("\nTo-Do List App")
        print("1. Add Task")
        print("2. View Tasks")
        print("3. Quit")
        
        choice = input("Enter your choice (1/2/3): ")
        
        if choice == "1":
            add_task()
        elif choice == "2":
            view_tasks()
        elif choice == "3":
            break
        else:
            print("Invalid choice. Try again!")

if __name__ == '__main__':
    main()