# Restaurant Menu Recommendations

class MenuItem:
    def __init__(self, name, description, price, vegetarian, gluten_free):
        self.name = name
        self.description = description
        self.price = price
        self.vegetarian = vegetarian
        self.gluten_free = gluten_free

class UserPreferences:
    def __init__(self, dietary_restrictions, favorite_cuisine):
        self.dietary_restrictions = dietary_restrictions
        self.favorite_cuisine = favorite_cuisine

def recommend_menu_items(menu_items, user_preferences):
    recommended_items = []
    
    for item in menu_items:
        if (user_preferences.dietary_restrictions & item.vegetarian and 
            user_preferences.dietary_restrictions & item.gluten_free):
            recommended_items.append(item)
        elif user_preferences.favorite_cuisine == "Italian" and not item.vegetarian:
            recommended_items.append(item)
    
    return recommended_items

def main():
    menu_items = [
        MenuItem("Spaghetti Bolognese", "Classic Italian dish with spaghetti, ground beef, and tomato sauce.", 15.99, False, True),
        MenuItem("Veggie Burger", "A vegetarian burger made with black beans, corn, and avocado.", 12.99, True, True),
        MenuItem("Grilled Chicken Caesar Salad", "A classic salad with grilled chicken, romaine lettuce, and croutons.", 14.99, False, False),
        MenuItem("Veggie Wrap", "A wrap filled with roasted vegetables, hummus, and mixed greens.", 11.99, True, True)
    ]
    
    user_preferences = UserPreferences(1 << 0 | 1 << 1, "Italian")
    
    recommended_items = recommend_menu_items(menu_items, user_preferences)
    
    print("Recommended Menu Items:")
    for item in recommended_items:
        print(f"{item.name} - {item.description}")

if __name__ == '__main__':
    main()