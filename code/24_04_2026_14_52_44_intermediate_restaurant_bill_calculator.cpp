#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define a struct for menu items
struct MenuItem {
    string name;
    double price;
};

// Function to calculate total bill
double calculateTotalBill(const vector<MenuItem>& menuItems, int quantity) {
    double total = 0.0;
    for (const auto& item : menuItems) {
        total += item.price * quantity;
    }
    return total;
}

int main() {
    // Define menu items
    vector<MenuItem> menuItems = {
        {"Burger", 8.99},
        {"Fries", 2.49},
        {"Soda", 1.99},
        {"Milkshake", 4.99}
    };

    int quantity;
    cout << "Enter the quantity of items: ";
    cin >> quantity;

    // Calculate total bill
    double totalBill = calculateTotalBill(menuItems, quantity);

    cout << "Total bill: $" << totalBill << endl;

    return 0;
}
