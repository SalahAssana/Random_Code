# To-Do List App
# BEGINNER complexity project

to_do_list = []

def add_task(task):
    global to_do_list
    to_do_list.append(task)
    print(f"Task '{task}' added to the list.")

def view_tasks():
    global to_do_list
    if not to_do_list:
        print("No tasks in the list.")
    else:
        print("Your To-Do List:")
        for task in to_do_list:
            print(task)

if __name__ == '__main__':
    while True:
        print("\n1. Add Task\n2. View Tasks\n3. Quit")
        choice = input("Choose an option: ")
        
        if choice == '1':
            task = input("Enter a new task: ")
            add_task(task)
        elif choice == '2':
            view_tasks()
        elif choice == '3':
            print("Goodbye!")
            break
        else:
            print("Invalid option. Please try again.")