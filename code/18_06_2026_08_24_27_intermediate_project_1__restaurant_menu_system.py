# Project 1: Restaurant Menu System

class MenuItem:
    def __init__(self, name, price):
        self.name = name
        self.price = price

class MenuSystem:
    def __init__(self):
        self.menu = []

    def add_item(self, item_name, item_price):
        if not any(item.name == item_name for item in self.menu):
            self.menu.append(MenuItem(item_name, item_price))
        else:
            print("Item already exists on the menu.")

    def remove_item(self, item_name):
        self.menu = [item for item in self.menu if item.name != item_name]

    def display_menu(self):
        for item in self.menu:
            print(f"{item.name}: ${item.price:.2f}")

    def calculate_total_cost(self):
        return sum(item.price for item in self.menu)

def main():
    menu_system = MenuSystem()
    
    while True:
        print("\n1. Add Item\n2. Remove Item\n3. Display Menu\n4. Calculate Total Cost\n5. Exit")
        choice = input("Choose an option: ")
        
        if choice == "1":
            item_name = input("Enter the name of the item: ")
            item_price = float(input("Enter the price of the item: "))
            menu_system.add_item(item_name, item_price)
        elif choice == "2":
            item_name = input("Enter the name of the item to remove: ")
            menu_system.remove_item(item_name)
        elif choice == "3":
            menu_system.display_menu()
        elif choice == "4":
            print(f"Total cost: ${menu_system.calculate_total_cost():.2f}")
        elif choice == "5":
            break
        else:
            print("Invalid option. Please choose a valid option.")

if __name__ == '__main__':
    main()