# To-Do List
# A simple program to manage tasks and due dates.

tasks = [
    {"task": "Buy milk", "due_date": "2022-12-25"},
    {"task": "Finish project", "due_date": "2023-01-15"},
]

def display_tasks():
    print("To-Do List:")
    for task in tasks:
        print(f"Task: {task['task']}, Due Date: {task['due_date']}")

def add_task(task_name, due_date):
    new_task = {"task": task_name, "due_date": due_date}
    tasks.append(new_task)
    print("New task added!")

if __name__ == '__main__':
    while True:
        print("\n1. Display To-Do List")
        print("2. Add a Task")
        print("3. Quit")
        
        choice = input("Choose an option: ")
        
        if choice == "1":
            display_tasks()
        elif choice == "2":
            task_name = input("Enter the task name: ")
            due_date = input("Enter the due date (YYYY-MM-DD): ")
            add_task(task_name, due_date)
        elif choice == "3":
            print("Goodbye!")
            break
        else:
            print("Invalid option. Please choose again.")