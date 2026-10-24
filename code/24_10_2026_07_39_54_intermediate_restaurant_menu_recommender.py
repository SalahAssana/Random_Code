# Restaurant Menu Recommender
import random

class MenuItem:
    def __init__(self, name, description, price, dietary_restrictions):
        self.name = name
        self.description = description
        self.price = price
        self.dietary_restrictions = set(dietary_restrictions.split(","))

class Customer:
    def __init__(self, dietary_restrictions):
        self.dietary_restrictions = set(dietary_restrictions.split(","))

def recommend_items(menu_items, customer, num_recommendations):
    recommended_items = []
    for item in menu_items:
        if all(restriction not in item.dietary_restrictions for restriction in customer.dietary_restrictions):
            recommended_items.append(item)
    return random.sample(recommended_items, min(num_recommendations, len(recommended_items)))

def main():
    # Synthetic data
    menu_items = [
        MenuItem("Burger", "A juicy beef burger with lettuce and tomato", 10.99, ["gluten"]),
        MenuItem("Salad", "A fresh mix of greens with veggies and vinaigrette", 8.99, []),
        MenuItem("Veggie Burger", "A vegetarian burger with black beans and avocado", 11.99, ["gluten"]),
        MenuItem("Fries", "Crispy french fries served with a side of ketchup", 4.99, ["gluten"]),
    ]

    customers = [
        Customer("gluten"),
        Customer("dairy"),
        Customer("vegetarian"),
        Customer("vegan"),
    ]

    for customer in customers:
        print(f"Recommendations for {customer.dietary_restrictions}:")
        recommendations = recommend_items(menu_items, customer, 3)
        for item in recommendations:
            print(f"{item.name} - {item.description} (${item.price})")

if __name__ == '__main__':
    main()