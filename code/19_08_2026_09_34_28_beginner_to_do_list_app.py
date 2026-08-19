# To-Do List App

to_do_list = []

def add_task(task):
    to_do_list.append({"task": task, "done": False})

def remove_task(index):
    try:
        del to_do_list[index]
    except IndexError:
        print("Invalid index!")

def mark_done(index):
    try:
        to_do_list[index]["done"] = True
    except IndexError:
        print("Invalid index!")

def display_tasks():
    for i, task in enumerate(to_do_list):
        status = "Done" if task["done"] else "Not Done"
        print(f"{i+1}. {task['task']} - {status}")

if __name__ == '__main__':
    while True:
        print("\nOptions:")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. Mark Done")
        print("4. Display Tasks")
        print("5. Quit")

        option = input("Choose an option: ")

        if option == "1":
            task = input("Enter the task: ")
            add_task(task)
        elif option == "2":
            index = int(input("Enter the task number to remove: "))
            remove_task(index-1)
        elif option == "3":
            index = int(input("Enter the task number to mark done: "))
            mark_done(index-1)
        elif option == "4":
            display_tasks()
        elif option == "5":
            break
        else:
            print("Invalid option. Please try again.")