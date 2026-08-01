#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <map>
#include <vector>

using namespace std;

// Stock class to represent individual stocks
class Stock {
public:
    string symbol;
    double price;
    int shares;

    Stock(string symbol, double price, int shares) : symbol(symbol), price(price), shares(shares) {}

    // Update the stock's price and number of shares
    void updatePrice(double newPrice, int newShares) {
        price = newPrice;
        shares = newShares;
    }
};

// Transaction class to represent individual transactions
class Transaction {
public:
    string type; // "buy" or "sell"
    double price;
    int shares;

    Transaction(string type, double price, int shares) : type(type), price(price), shares(shares) {}
};

// StockMarketSimulator class to manage the stock market simulation
class StockMarketSimulator {
private:
    map<string, Stock> stocks; // Map of stocks and their current prices
    queue<Transaction> transactions; // Queue of pending transactions
    mutex mtx; // Mutex for thread-safe access

public:
    // Add a new stock to the market
    void addStock(string symbol, double price, int shares) {
        Stock newStock(symbol, price, shares);
        stocks[symbol] = newStock;
    }

    // Process a transaction
    void processTransaction(Transaction transaction) {
        lock_guard<mutex> lock(mtx);

        string symbol = transaction.type == "buy" ? "AAPL" : "MSFT";
        Stock& stock = stocks[symbol];

        if (transaction.type == "buy") {
            stock.shares += transaction.shares;
        } else {
            stock.shares -= transaction.shares;

            // Check for and handle short selling
            if (stock.shares < 0) {
                // Short sell not allowed, cancel the transaction
                transactions.pop();
            }
        }

        // Update the stock's price based on the transaction
        stock.updatePrice(transaction.price, stock.shares);
    }

    // Run the simulation for a specified number of ticks
    void runSimulation(int numTicks) {
        vector<thread> threads;

        for (int i = 0; i < numTicks; i++) {
            thread t([this]() {
                while (true) {
                    Transaction transaction;
                    {
                        lock_guard<mutex> lock(mtx);
                        if (!transactions.empty()) {
                            transaction = transactions.front();
                            transactions.pop();
                            break;
                        }
                    }
                    this->processTransaction(transaction);
                }
            });
            threads.push_back(move(t));
        }

        for (thread& t : threads) {
            t.join();
        }
    }

    // Add a new transaction to the queue
    void addTransaction(Transaction transaction) {
        lock_guard<mutex> lock(mtx);
        transactions.push(transaction);
    }
};

int main() {
    StockMarketSimulator simulator;

    // Initialize the stock market with some initial conditions
    simulator.addStock("AAPL", 100.0, 10000);
    simulator.addStock("MSFT", 50.0, 5000);

    // Simulate transactions for 10 ticks
    simulator.runSimulation(10);

    return 0;
}