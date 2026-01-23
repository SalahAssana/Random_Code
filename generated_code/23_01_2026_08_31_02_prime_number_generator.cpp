#include <iostream>
#include <vector>

// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1)
        return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

// Function to generate and print prime numbers up to a given number
void generatePrimeNumbers(int num) {
    std::vector<int> primes;
    for (int i = 2; i <= num; i++) {
        if (isPrime(i)) {
            primes.push_back(i);
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
}

int main() {
    int num;
    std::cout << "Enter a number: ";
    std::cin >> num;
    generatePrimeNumbers(num);
    return 0;
}