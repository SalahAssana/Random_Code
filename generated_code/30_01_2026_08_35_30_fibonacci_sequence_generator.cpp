#include <iostream>
using namespace std;

void generateFibonacci(int n) {
    int t1 = 0, t2 = 1;
    cout << "Fibonacci Series: ";

    for (int i = 1; i <= n; ++i) {
        cout << t1 << " ";
        int sum = t1 + t2;
        t1 = t2;
        t2 = sum;
    }
    cout << endl;
}

int main() {
    int numTerms;
    cout << "Enter the number of terms: ";
    cin >> numTerms;
    generateFibonacci(numTerms);
    return 0;
}