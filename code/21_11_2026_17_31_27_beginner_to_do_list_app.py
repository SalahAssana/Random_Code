# To-Do List App

# Import necessary modules
import todo_list_app as tda  # You can rename this to any name you like

def print_menu():
    """Prints the menu for the user"""
    print("To-Do List App")
    print("----------------")
    print("1. Add Task")
    print("2. Remove Task")
    print("3. View Tasks")
    print("4. Quit")

def add_task(todo_list):
    """Allows the user to add a task to the list"""
    task = input("Enter your task: ")
    todo_list.append(task)
    print(f"Task '{task}' added successfully!")

def remove_task(todo_list):
    """Allows the user to remove a task from the list"""
    if not todo_list:
        print("No tasks in the list!")
    else:
        task_num = int(input("Enter the number of the task to remove (1-based): "))
        if 1 <= task_num <= len(todo_list):
            removed_task = todo_list.pop(task_num - 1)
            print(f"Task '{removed_task}' removed successfully!")
        else:
            print("Invalid task number!")

def view_tasks(todo_list):
    """Displays all tasks in the list"""
    if not todo_list:
        print("No tasks in the list!")
    else:
        for i, task in enumerate(todo_list, start=1):
            print(f"{i}. {task}")

def main():
    """Main function to handle user interactions"""
    todo_list = []
    
    while True:
        print_menu()
        choice = int(input("Enter your choice: "))
        
        if choice == 1:
            add_task(todo_list)
        elif choice == 2:
            remove_task(todo_list)
        elif choice == 3:
            view_tasks(todo_list)
        elif choice == 4:
            break
        else:
            print("Invalid choice! Try again.")

if __name__ == '__main__':
    main()