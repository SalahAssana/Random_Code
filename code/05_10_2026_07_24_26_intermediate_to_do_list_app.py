# To-Do List App in Python

class TodoList:
    def __init__(self):
        self.tasks = []

    def add_task(self, task):
        if not isinstance(task, str) or len(task) == 0:
            raise ValueError("Task must be a non-empty string")
        self.tasks.append({"task": task, "completed": False})

    def remove_task(self, index):
        try:
            del self.tasks[index]
        except IndexError:
            raise IndexError("Index out of range")

    def mark_completed(self, index):
        try:
            self.tasks[index]["completed"] = True
        except IndexError:
            raise IndexError("Index out of range")

    def display_tasks(self):
        for i, task in enumerate(self.tasks):
            status = "Completed" if task["completed"] else "Not completed"
            print(f"{i+1}. {task['task']} - {status}")

def main():
    todo_list = TodoList()

    while True:
        print("\nOptions:")
        print("1. Add task")
        print("2. Remove task")
        print("3. Mark task as completed")
        print("4. Display tasks")
        print("5. Exit")

        choice = input("Choose an option: ")

        if choice == "1":
            task = input("Enter a new task: ")
            todo_list.add_task(task)
        elif choice == "2":
            index = int(input("Enter the task number to remove: "))
            todo_list.remove_task(index - 1)
        elif choice == "3":
            index = int(input("Enter the task number to mark as completed: "))
            todo_list.mark_completed(index - 1)
        elif choice == "4":
            todo_list.display_tasks()
        elif choice == "5":
            break
        else:
            print("Invalid option. Please choose again.")

if __name__ == '__main__':
    main()