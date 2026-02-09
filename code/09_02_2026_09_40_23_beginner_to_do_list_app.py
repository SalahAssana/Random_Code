# To-Do List App

to_do_list = []

def add_task(task):
    to_do_list.append({"task": task, "done": False})

def remove_task(index):
    if index < len(to_do_list):
        del to_do_list[index]
    else:
        print("Task not found")

def display_tasks():
    for i, task in enumerate(to_do_list):
        status = "Done" if task["done"] else "Not Done"
        print(f"{i+1}. {task['task']} - {status}")

if __name__ == '__main__':
    while True:
        print("\nTo-Do List App")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. Display Tasks")
        print("4. Quit")
        
        choice = input("Enter your choice: ")
        
        if choice == "1":
            task = input("Enter the task: ")
            add_task(task)
        elif choice == "2":
            index = int(input("Enter the task number to remove: "))
            remove_task(index-1)
        elif choice == "3":
            display_tasks()
        elif choice == "4":
            break
        else:
            print("Invalid choice. Please try again.")