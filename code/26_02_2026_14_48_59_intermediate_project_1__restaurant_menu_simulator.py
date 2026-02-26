# Restaurant Menu Simulator
# Author: [Your Name]
# Date: [Current Date]

class MenuItem:
    def __init__(self, name, price):
        self.name = name
        self.price = price

class Order:
    def __init__(self):
        self.items = []

    def add_item(self, item_name):
        for item in menu_items:
            if item.name == item_name:
                self.items.append(item)
                return
        print(f"Item '{item_name}' not found.")

    def calculate_total(self):
        total = 0
        for item in self.items:
            total += item.price
        return total

class Bill:
    def __init__(self, order):
        self.order = order
        self.total = order.calculate_total()

    def print_bill(self):
        print(f"Order Total: ${self.total:.2f}")
        for i, item in enumerate(self.order.items, 1):
            print(f"{i}. {item.name} - ${item.price:.2f}")

if __name__ == '__main__':
    menu_items = [
        MenuItem("Burger", 8.99),
        MenuItem("Fries", 3.49),
        MenuItem("Salad", 4.99),
        MenuItem("Soda", 1.99)
    ]

    order = Order()
    while True:
        print("\nMenu:")
        for i, item in enumerate(menu_items):
            print(f"{i+1}. {item.name} - ${item.price:.2f}")
        choice = input("Enter the number of your selection (or 'q' to quit): ")
        if choice.lower() == 'q':
            break
        elif choice.isdigit():
            order.add_item(menu_items[int(choice) - 1].name)
        else:
            print("Invalid selection. Try again.")

    bill = Bill(order)
    bill.print_bill()