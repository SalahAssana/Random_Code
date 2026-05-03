# Shopping Cart System
class Product:
    def __init__(self, name, price):
        self.name = name
        self.price = price

class ShoppingCart:
    def __init__(self):
        self.items = {}

    def add_item(self, product, quantity):
        if product not in self.items:
            self.items[product] = 0
        self.items[product] += quantity

    def remove_item(self, product, quantity):
        if product in self.items and self.items[product] >= quantity:
            self.items[product] -= quantity
            if self.items[product] == 0:
                del self.items[product]
        else:
            print("Not enough quantity to remove.")

    def get_total_price(self):
        return sum([product.price * quantity for product, quantity in self.items.items()])

def main():
    cart = ShoppingCart()

    # Add some products
    cart.add_item(Product("Apple", 0.99), 2)
    cart.add_item(Product("Banana", 0.25), 3)

    print(f"Total price: {cart.get_total_price()}")

    # Remove a few items
    cart.remove_item(Product("Apple", 0.99), 1)
    cart.remove_item(Product("Banana", 0.25), 1)

    print(f"New total price: {cart.get_total_price()}")

if __name__ == '__main__':
    main()