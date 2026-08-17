import requests
from bs4 import BeautifulSoup
import json
from datetime import datetime
from threading import Thread
from queue import Queue

class ShopBot:
    def __init__(self):
        self.url = "https://example.com"  # Replace with your online shopping website URL
        self.products = []
        self.queue = Queue()

    def get_products(self, url):
        response = requests.get(url)
        soup = BeautifulSoup(response.text, 'html.parser')
        products = soup.find_all('div', {'class': 'product'})
        for product in products:
            name = product.find('h2').text
            price = product.find('span', {'class': 'price'}).text
            self.products.append({'name': name, 'price': float(price.replace('$', ''))))

    def purchase_product(self, product):
        data = {'product_name': product['name'], 'price': product['price']}
        response = requests.post(f"{self.url}/purchase", json=data)
        if response.status_code == 200:
            print(f"Purchased {product['name']} for ${product['price']}")
        else:
            print(f"Error purchasing {product['name']}: {response.text}")

    def run(self):
        thread = Thread(target=self.get_products, args=(self.url,))
        thread.start()
        while True:
            if not self.queue.empty():
                product = self.queue.get()
                self.purchase_product(product)

    def main_loop(self):
        while True:
            print("1. Start shopping")
            print("2. Exit")
            choice = input("Choose an option: ")
            if choice == '1':
                for _ in range(5):  # Simulate 5 products
                    product = {'name': f"Product {_+1}", 'price': 50.0}
                    self.queue.put(product)
                self.run()
            elif choice == '2':
                print("Exiting...")
                break
            else:
                print("Invalid option")

if __name__ == '__main__':
    bot = ShopBot()
    bot.main_loop()