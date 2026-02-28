#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Menu Item struct
struct MenuItem {
    string name;
    double price;
};

// Restaurant class
class Restaurant {
public:
    vector<MenuItem> menuItems;
    int orderNumber = 0;

    void addItem(const string& name, double price) {
        MenuItem item = {name, price};
        menuItems.push_back(item);
    }

    void displayMenu() const {
        for (const auto& item : menuItems) {
            cout << "Item: " << item.name << ", Price: $" << item.price << endl;
        }
    }

    void placeOrder(const string& itemName) {
        bool found = false;
        for (auto& item : menuItems) {
            if (item.name == itemName) {
                double total = item.price + 0.1; // add tax
                cout << "Your order: " << itemName << ", Total: $" << total << endl;
                orderNumber++;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Item not found on the menu." << endl;
        }
    }

};

int main() {
    Restaurant restaurant;

    // Add items to the menu
    restaurant.addItem("Burger", 8.99);
    restaurant.addItem("Pizza", 12.99);
    restaurant.addItem("Salad", 6.99);

    // Display the menu
    cout << "Current Menu:" << endl;
    restaurant.displayMenu();

    // Place an order
    string order;
    cout << "Enter the item name to place an order: ";
    cin >> order;
    restaurant.placeOrder(order);

    return 0;
}