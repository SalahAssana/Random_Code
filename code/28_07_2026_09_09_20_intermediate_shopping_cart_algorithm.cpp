#include <iostream>
#include <algorithm>
using namespace std;

// Define a struct to represent an item
struct Item {
    string name;
    int quantity;
    double price;
};

// Function to add items to the cart
void addItem(Item* item, int& index) {
    // Find the next available slot in the array
    for (int i = 0; i < index; i++) {
        if (!item[i].name.empty()) {
            break;
        }
    }

    // Add the new item at the found position or append to the end
    item[i].name = item->name;
    item[i].quantity = item->quantity;
    item[i].price = item->price;

    index++;
}

// Function to remove items from the cart
void removeItem(Item* item, int& index) {
    // Find the last non-empty slot in the array
    for (int i = index - 1; i >= 0; i--) {
        if (!item[i].name.empty()) {
            break;
        }
    }

    // Shift all items to the left and truncate at the found position
    while (i > 0) {
        item[i] = item[i - 1];
        i--;
    }

    index--;
}

// Function to display the cart contents
void displayCart(Item* item, int index) {
    cout << "Shopping Cart Contents:" << endl;
    for (int i = 0; i < index; i++) {
        cout << "Name: " << item[i].name << ", Quantity: " << item[i].quantity << ", Price: $" << fixed << setprecision(2) << item[i].price << endl;
    }
}

// Function to calculate the total cost of items in the cart
double calculateTotalCost(Item* item, int index) {
    double total = 0.0;
    for (int i = 0; i < index; i++) {
        total += item[i].quantity * item[i].price;
    }
    return total;
}

int main() {
    // Initialize the cart with an array of size 10
    Item* cart = new Item[10];
    int index = 0;

    // Add some items to the cart
    addItem({{"Apple", 1, 1.99}, "Apple", 2, 1.99}, index);
    addItem({{"Banana", 3, 0.49}, "Banana", 4, 0.49}, index);

    // Display the cart contents
    displayCart(cart, index);

    // Remove an item from the cart
    removeItem(cart, index);
    displayCart(cart, index);

    // Calculate and display the total cost of items in the cart
    double total = calculateTotalCost(cart, index);
    cout << "Total Cost: $" << fixed << setprecision(2) << total << endl;

    delete[] cart;
    return 0;
}