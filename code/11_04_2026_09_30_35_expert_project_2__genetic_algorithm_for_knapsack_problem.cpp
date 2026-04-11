#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int value;
};

class Knapsack {
public:
    Knapsack(int capacity) : capacity(capacity), items() {}

    void addItem(int weight, int value) {
        items.push_back({weight, value});
    }

    vector<int> solve() {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);

        vector<Item> population(100);
        for (auto& item : population) {
            int weight = 0, value = 0;
            for (int i = 0; i < items.size(); ++i) {
                if (dis(gen) < static_cast<double>(items[i].value) / items[i].weight) {
                    weight += items[i].weight;
                    value += items[i].value;
                }
            }
            item.weight = weight;
            item.value = value;
        }

        vector<Item> bestSolution(0);
        for (int generation = 0; generation < 1000; ++generation) {
            vector<Item> nextGeneration(0);
            for (auto& parent : population) {
                int crossoverPoint = rand() % items.size();
                Item child1, child2;
                child1.weight = parent.weight + items[crossoverPoint].weight;
                child1.value = parent.value + items[crossoverPoint].value;
                child2.weight = parent.weight - items[crossoverPoint].weight;
                child2.value = parent.value - items[crossoverPoint].value;

                for (int i = 0; i < items.size(); ++i) {
                    if (dis(gen) < static_cast<double>(items[i].value) / items[i].weight) {
                        if (child1.weight + items[i].weight <= capacity)
                            child1.weight += items[i].weight, child1.value += items[i].value;
                        if (child2.weight - items[i].weight >= 0)
                            child2.weight -= items[i].weight, child2.value -= items[i].value;
                    }
                }

                nextGeneration.push_back(child1);
                nextGeneration.push_back(child2);
            }

            population = nextGeneration;

            Item bestItem = *max_element(population.begin(), population.end(), [](const auto& a, const auto& b) {
                return a.value < b.value || (a.value == b.value && a.weight > b.weight);
            });

            if (!bestSolution.size() || bestItem.value > bestSolution[0].value || (bestItem.value == bestSolution[0].value && bestItem.weight > bestSolution[0].weight)) {
                bestSolution = {bestItem};
            } else if (bestItem.value == bestSolution[0].value && bestItem.weight == bestSolution[0].weight) {
                bestSolution.push_back(bestItem);
            }
        }

        return vector<int>(bestSolution.begin(), bestSolution.end());
    }

private:
    int capacity;
    vector<Item> items;
};

int main() {
    Knapsack knapsack(10);
    knapsack.addItem(2, 3);
    knapsack.addItem(3, 4);
    knapsack.addItem(5, 6);
    knapsack.addItem(7, 8);

    vector<int> solution = knapsack.solve();

    cout << "Best solution: ";
    for (int i : solution) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}