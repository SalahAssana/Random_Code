# To-Do List App

to_do_list = []

def add_task(task):
    global to_do_list
    if task != "":
        to_do_list.append(task)

def remove_task(index):
    global to_do_list
    try:
        del to_do_list[index]
    except IndexError:
        print("Invalid index. Please check the list again.")

def view_tasks():
    global to_do_list
    for i, task in enumerate(to_do_list, start=1):
        print(f"{i}. {task}")

if __name__ == '__main__':
    while True:
        print("\nTo-Do List App")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. View Tasks")
        print("4. Quit")
        
        choice = input("Choose an option: ")
        
        if choice == "1":
            task = input("Enter a new task: ")
            add_task(task)
        elif choice == "2":
            index = int(input("Enter the index of the task to remove: "))
            remove_task(index - 1)  # list indices start at 0
        elif choice == "3":
            view_tasks()
        elif choice == "4":
            break
        else:
            print("Invalid option. Please choose again.")