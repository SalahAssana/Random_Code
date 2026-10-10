#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Game {
public:
    string name;
    int quantity;
    double price;

    Game(string n, int q, double p) : name(n), quantity(q), price(p) {}
};

class GameStore {
private:
    map<string, vector<Game>> inventory;

public:
    void addGame(string gameName, Game newGame) {
        if (inventory.find(gameName) == inventory.end()) {
            inventory[gameName] = {};
        }
        inventory[gameName].push_back(newGame);
    }

    void removeGame(string gameName) {
        if (inventory.find(gameName) != inventory.end()) {
            inventory.erase(gameName);
        }
    }

    bool checkAvailability(string gameName, int quantityToCheck) {
        if (inventory.find(gameName) == inventory.end()) {
            return false;
        }
        for (Game game : inventory[gameName]) {
            if (game.quantity >= quantityToCheck) {
                return true;
            }
        }
        return false;
    }

    double calculateTotalValue() {
        double total = 0.0;
        for (auto& pair : inventory) {
            for (Game game : pair.second) {
                total += game.price * game.quantity;
            }
        }
        return total;
    }

    void printInventory() {
        for (auto& pair : inventory) {
            cout << "Game: " << pair.first << endl;
            for (Game game : pair.second) {
                cout << "  Name: " << game.name << ", Quantity: " << game.quantity << ", Price: $" << game.price << endl;
            }
        }
    }
};

int main() {
    GameStore store;

    // Add games
    Game newGame1("The Last of Us", 10, 60.0);
    Game newGame2("God of War", 5, 70.0);
    store.addGame("Action Games", newGame1);
    store.addGame("Action Games", newGame2);
    store.addGame("Role Playing Games", Game("The Elder Scrolls V: Skyrim", 8, 50.0));

    // Print inventory
    store.printInventory();

    // Check availability
    cout << "Is there enough quantity of 'The Last of Us' to fulfill an order of 5 copies? "
         << (store.checkAvailability("Action Games", 5) ? "Yes" : "No") << endl;

    // Calculate total value
    double totalValue = store.calculateTotalValue();
    cout << "Total value of all games: $" << totalValue << endl;

    // Remove game
    store.removeGame("Role Playing Games");

    return 0;
}