#include <iostream>
#include <string>
#include <map>

using namespace std;

// Structure to represent an item
struct Item {
    string name;
    double price;
};

// Function to add an item to the cart
void addItem(map<string, int> &cart, const string &name, const double &price) {
    if (cart.find(name) != cart.end()) {
        // If the item is already in the cart, increment its quantity
        cart[name]++;
    } else {
        // Add the new item to the cart with a quantity of 1
        cart[name] = 1;
    }
}

// Function to remove an item from the cart
void removeItem(map<string, int> &cart, const string &name) {
    if (cart.find(name) != cart.end()) {
        // If the item is in the cart, decrement its quantity
        cart[name]--;
        if (cart[name] == 0) {
            // If the item's quantity becomes 0, remove it from the cart
            cart.erase(name);
        }
    }
}

// Function to calculate the total cost of the items in the cart
double calculateTotalCost(const map<string, int> &cart) {
    double total = 0.0;
    for (const auto &item : cart) {
        total += item.second * item.first.second; // Calculate the cost of each item and add it to the total
    }
    return total;
}

// Function to display the contents of the cart
void displayCart(const map<string, int> &cart) {
    cout << "Shopping Cart:" << endl;
    for (const auto &item : cart) {
        cout << item.first << ": x" << item.second << ", $" << item.first.second * item.second << endl;
    }
}

int main() {
    map<string, Item> items = {
        {"Apple", 0.99},
        {"Banana", 0.49},
        {"Carrot", 1.29}
    };

    map<string, int> cart;

    while (true) {
        cout << "Shopping Cart Menu:" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Remove Item" << endl;
        cout << "3. View Cart" << endl;
        cout << "4. Check Out" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                double price;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter item price: ";
                cin >> price;
                addItem(cart, name, price);
                break;
            }
            case 2: {
                string name;
                cout << "Enter item name to remove: ";
                cin >> name;
                removeItem(cart, name);
                break;
            }
            case 3:
                displayCart(cart);
                break;
            case 4: {
                double total = calculateTotalCost(cart);
                cout << "Total Cost: $" << total << endl;
                cart.clear(); // Clear the cart after checkout
                break;
            }
            case 5:
                return 0; // Exit the program

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}