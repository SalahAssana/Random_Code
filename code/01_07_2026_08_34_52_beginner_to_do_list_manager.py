# To-Do List Manager
# Beginner-level Python project to manage tasks and prioritize them based on due dates.

tasks = [
    {"name": "Task 1", "due_date": "2023-02-20"},
    {"name": "Task 2", "due_date": "2023-03-15"},
    {"name": "Task 3", "due_date": "2023-04-10"}
]

def print_tasks():
    """Print all tasks in the list."""
    for task in tasks:
        print(f"Name: {task['name']}, Due Date: {task['due_date']}")

def add_task(name, due_date):
    """Add a new task to the list."""
    tasks.append({"name": name, "due_date": due_date})

def prioritize_tasks():
    """Sort tasks by due date in ascending order."""
    tasks.sort(key=lambda x: x["due_date"])

if __name__ == '__main__':
    print("To-Do List Manager")
    while True:
        print("\nOptions:")
        print("1. Print all tasks")
        print("2. Add a new task")
        print("3. Prioritize tasks by due date")
        print("4. Exit")

        choice = input("Enter your choice: ")

        if choice == "1":
            print_tasks()
        elif choice == "2":
            name = input("Enter the task name: ")
            due_date = input("Enter the task due date (YYYY-MM-DD): ")
            add_task(name, due_date)
        elif choice == "3":
            prioritize_tasks()
        elif choice == "4":
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please try again.")