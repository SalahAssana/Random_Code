#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// Structure to represent a node in the graph
struct Node {
    int id;
    std::vector<int> neighbors;
};

// Function to generate a random permutation of the nodes
std::vector<int> randomPermutation(const std::vector<Node>& nodes, const size_t& populationSize) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, nodes.size() - 1);

    std::vector<int> permutation(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        permutation[i] = nodes[dis(gen)].id;
    }
    return permutation;
}

// Function to calculate the fitness of a solution
double calculateFitness(const std::vector<Node>& nodes, const std::vector<int>& solution) {
    double totalDistance = 0.0;

    for (int i = 0; i < solution.size() - 1; ++i) {
        Node& node = nodes[solution[i]];
        Node& nextNode = nodes[solution[i + 1]];
        totalDistance += static_cast<double>(node.id * nextNode.id);
    }

    return 1.0 / (totalDistance + 1e-6); // Add a small value to avoid division by zero
}

// Function to perform crossover on two parent solutions
std::vector<int> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
    size_t crossoverPoint = rand() % (parent1.size());
    std::vector<int> child(parent1.begin(), parent1.begin() + crossoverPoint);
    for (int i = 0; i < parent2.size(); ++i) {
        int nodeID = parent2[i];
        bool found = false;
        for (int j = 0; j < child.size(); ++j) {
            if (child[j] == nodeID) {
                found = true;
                break;
            }
        }
        if (!found) {
            child.push_back(nodeID);
        }
    }

    return child;
}

// Function to mutate a solution
std::vector<int> mutate(const std::vector<int>& solution, const double& mutationRate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < solution.size(); ++i) {
        if (dis(gen) < mutationRate) {
            int nodeID = rand() % nodes.size();
            while (std::find(solution.begin(), solution.end(), nodeID) != solution.end()) {
                nodeID = rand() % nodes.size();
            }
            std::swap(solution[i], nodeID);
        }
    }

    return solution;
}

// Main function
int main() {
    // Define the graph as a vector of nodes
    std::vector<Node> nodes = {{0, {1, 2}}, {1, {0, 3, 4}}, {2, {0, 5}}, {3, {1}}, {4, {1}}, {5, {2}}};

    // Set the population size and mutation rate
    const size_t populationSize = 100;
    const double mutationRate = 0.01;

    // Initialize the population with random solutions
    std::vector<std::vector<int>> population(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        population[i] = randomPermutation(nodes, populationSize);
    }

    // Perform genetic algorithm iterations
    for (int generation = 0; generation < 100; ++generation) {
        std::vector<std::pair<double, std::vector<int>>> fitnessValues;

        // Calculate the fitness of each solution in the population
        for (const auto& solution : population) {
            double fitness = calculateFitness(nodes, solution);
            fitnessValues.emplace_back(fitness, solution);
        }

        // Select parents for crossover and mutation based on their fitness
        std::vector<std::pair<double, std::vector<int>>> parents;
        for (int i = 0; i < populationSize / 2; ++i) {
            auto parent1 = *std::max_element(fitnessValues.begin(), fitnessValues.end(),
                                             [](const auto& a, const auto& b) { return a.first < b.first; });
            fitnessValues.erase(std::remove_if(fitnessValues.begin(), fitnessValues.end(),
                                               [parent1](const auto& pair) { return &pair == &parent1; }),
                                 fitnessValues.end());
            auto parent2 = *std::max_element(fitnessValues.begin(), fitnessValues.end(),
                                             [](const auto& a, const auto& b) { return a.first < b.first; });
            parents.emplace_back(parent1.first, parent1.second);
            parents.emplace_back(parent2.first, parent2.second);
        }

        // Perform crossover and mutation
        for (int i = 0; i < populationSize / 2; ++i) {
            std::vector<int> child = crossover(parents[i].second, parents[i + 1].second);
            child = mutate(child, mutationRate);
            population[i] = child;
            population[populationSize - i - 1] = crossover(parents[i].second, parents[i + 1].second);
        }
    }

    // Print the best solution
    auto bestSolution = *std::max_element(fitnessValues.begin(), fitnessValues.end(),
                                            [](const auto& a, const auto& b) { return a.first < b.first; });
    std::cout << "Best solution: ";
    for (int i = 0; i < bestSolution.second.size() - 1; ++i) {
        Node& node = nodes[bestSolution.second[i]];
        Node& nextNode = nodes[bestSolution.second[i + 1]];
        std::cout << node.id << " -> " << nextNode.id << " ";
    }
    std::cout << bestSolution.second.back() << std::endl;
    std::cout << "Fitness: " << bestSolution.first << std::endl;

    return 0;
}