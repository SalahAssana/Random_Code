# To-Do List App

# Import necessary modules
import tkinter as tk

class ToDoListApp:
    def __init__(self, root):
        self.root = root
        self.tasks = []

        # Create a label and entry field for user input
        self.label = tk.Label(root, text="Enter task:")
        self.label.pack()
        self.entry_field = tk.Entry(root)
        self.entry_field.pack()

        # Create a button to add tasks
        self.add_button = tk.Button(root, text="Add", command=self.add_task)
        self.add_button.pack()

        # Create a listbox to display tasks
        self.listbox = tk.Listbox(root)
        self.listbox.pack()

    def add_task(self):
        task = self.entry_field.get()
        if task != "":
            self.tasks.append(task)
            self.listbox.insert(tk.END, task)
            self.entry_field.delete(0, tk.END)

    # Create the main window
root = tk.Tk()
app = ToDoListApp(root)

# Start the Tkinter event loop
root.mainloop()

if __name__ == '__main__':
    pass