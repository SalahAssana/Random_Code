#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    // Set seed for random number generation
    srand(static_cast<unsigned int>(time(0)));

    // Set number of flips
    const int NUM_FLIPS = 100000;

    // Initialize counters
    int headsCount = 0;
    int tailsCount = 0;

    // Simulate coin flips
    for (int i = 0; i < NUM_FLIPS; ++i) {
        double randomNum = static_cast<double>(rand()) / RAND_MAX;
        if (randomNum < 0.5) {
            ++headsCount;
        } else {
            ++tailsCount;
        }
    }

    // Calculate and display results
    double headsProbability = static_cast<double>(headsCount) / NUM_FLIPS;
    double tailsProbability = static_cast<double>(tailsCount) / NUM_FLIPS;

    std::cout << "Heads probability: " << headsProbability * 100 << "%" << std::endl;
    std::cout << "Tails probability: " << tailsProbability * 100 << "%" << std::endl;

    return 0;
}