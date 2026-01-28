#include <iostream>
#include <vector>

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to generate prime numbers up to a given number
std::vector<int> generatePrimes(int num) {
    std::vector<int> primes;
    for (int i = 2; i <= num; i++) {
        if (isPrime(i)) primes.push_back(i);
    }
    return primes;
}

int main() {
    int num;
    std::cout << "Enter a number: ";
    std::cin >> num;
    
    std::vector<int> primes = generatePrimes(num);
    
    std::cout << "Prime numbers up to " << num << " are: ";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;
    
    return 0;
}