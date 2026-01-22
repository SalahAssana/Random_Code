#include <iostream>
using namespace std;

// Function to check if a number is prime
bool isPrime(int num) {
    // If number is less than 2, not prime
    if (num < 2)
        return false;
    
    // Check for divisibility from 2 to sqrt(num)
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }
    
    return true;
}

// Function to generate prime numbers in a range
void generatePrimes(int start, int end) {
    cout << "Prime numbers between " << start << " and " << end << ": ";
    for (int i = start; i <= end; i++) {
        if (isPrime(i))
            cout << i << " ";
    }
    cout << endl;
}

// Main function
int main() {
    int num;
    
    // Ask user to input a number
    cout << "Enter a number: ";
    cin >> num;
    
    // Check if the number is prime
    if (isPrime(num)) {
        cout << num << " is a prime number." << endl;
    } else {
        cout << num << " is not a prime number." << endl;
    }
    
    return 0;
}