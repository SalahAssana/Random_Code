# To-do list app in Python
tasks = []
def add_task(task):
    tasks.append({"task": task, "completed": False})

def remove_task(index):
    try:
        del tasks[index]
    except IndexError:
        print("Invalid index!")

def complete_task(index):
    try:
        tasks[index]["completed"] = True
    except IndexError:
        print("Invalid index!")

def display_tasks():
    for i, task in enumerate(tasks):
        status = "Completed" if task["completed"] else "Not completed"
        print(f"{i+1}. {task['task']} - {status}")

def main():
    while True:
        print("\nOptions:")
        print("1. Add task")
        print("2. Remove task")
        print("3. Complete task")
        print("4. Display tasks")
        print("5. Quit")
        
        option = input("Choose an option: ")
        
        if option == "1":
            task = input("Enter a task: ")
            add_task(task)
        elif option == "2":
            index = int(input("Enter the task number to remove: "))
            remove_task(index-1)
        elif option == "3":
            index = int(input("Enter the task number to complete: "))
            complete_task(index-1)
        elif option == "4":
            display_tasks()
        elif option == "5":
            break
        else:
            print("Invalid option. Please try again.")

if __name__ == '__main__':
    main()