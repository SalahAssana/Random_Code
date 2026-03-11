import sqlite3
import random

def create_database():
    conn = sqlite3.connect('mydatabase.db')
    c = conn.cursor()

    # Create table 'employees'
    c.execute('''CREATE TABLE IF NOT EXISTS employees (
                    id INTEGER PRIMARY KEY,
                    name TEXT,
                    age INTEGER,
                    department TEXT
                )''')

    # Insert 1000 random employees into the database
    for i in range(1000):
        name = f'Employee {i}'
        age = random.randint(20, 60)
        department = 'IT' if i % 3 == 0 else 'Sales'
        c.execute("INSERT INTO employees VALUES (NULL, ?, ?, ?)", (name, age, department))

    conn.commit()
    conn.close()

def query_database():
    conn = sqlite3.connect('mydatabase.db')
    c = conn.cursor()

    # Query to find all IT employees
    c.execute("SELECT * FROM employees WHERE department='IT'")

    # Fetch and print the results
    for row in c.fetchall():
        print(row)

    conn.close()

if __name__ == '__main__':
    create_database()
    query_database()