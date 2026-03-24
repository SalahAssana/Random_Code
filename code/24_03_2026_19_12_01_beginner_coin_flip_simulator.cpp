#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(0)); // seed random number generator
    
    int numFlips; // number of coin flips
    cout << "Enter the number of coin flips: ";
    cin >> numFlips;
    
    int heads = 0, tails = 0; // counts for heads and tails
    
    for(int i = 0; i < numFlips; i++) {
        double flip = (double)rand() / RAND_MAX; // simulate a random coin flip
        if(flip <= 0.5) { // heads or tails, 50/50 chance
            cout << "Heads ";
            if(flip <= 0.5)
                heads++;
            else
                tails++;
        } else {
            cout << "Tails ";
            if(flip > 0.5)
                heads++;
            else
                tails++;
        }
    }
    
    cout << endl;
    cout << "Heads: " << heads << ", Tails: " << tails << endl;
    
    return 0;
}