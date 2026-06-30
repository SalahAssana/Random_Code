import tkinter as tk
from tkinter import messagebox

class ToDoListApp:
    def __init__(self, root):
        self.root = root
        self.tasks = []
        self.task_list = tk.Listbox(self.root, width=40)
        self.task_list.pack()

        self.add_task_button = tk.Button(self.root, text="Add Task", command=self.add_task)
        self.add_task_button.pack()

        self.remove_task_button = tk.Button(self.root, text="Remove Task", command=self.remove_task)
        self.remove_task_button.pack()

    def add_task(self):
        task = self.task_entry.get()
        if task:
            self.tasks.append(task)
            self.task_list.insert(tk.END, task)
            self.task_entry.delete(0, tk.END)

    def remove_task(self):
        try:
            task_index = int(messagebox.askyesno("Remove Task", f"Are you sure you want to remove '{self.task_list.get(int(self.task_list.size())-1)}'?") and self.task_list.size() > 0
            if task_index is not None:
                self.tasks.pop(task_index)
                self.task_list.delete(task_index, tk.END)
        except ValueError as e:
            messagebox.showerror("Error", str(e))

    def run(self):
        self.root.title("To-Do List App")
        self.task_entry = tk.Entry(self.root, width=40)
        self.task_entry.pack()

        self.run_button = tk.Button(self.root, text="Run", command=self.add_task)
        self.run_button.pack()

if __name__ == '__main__':
    root = tk.Tk()
    app = ToDoListApp(root)
    app.run()
    root.mainloop()