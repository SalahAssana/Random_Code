#include <iostream>
#include <string>

using namespace std;

int main() {
    string userQuery;
    int response = 0;

    cout << "Simple Chatbot\n";
    cout << "Enter your query (type 'exit' to quit): ";

    while (true) {
        getline(cin, userQuery);
        
        if (userQuery == "exit") {
            break;
        }
        else if (userQuery == "hello") {
            response = 1; // Hello response
        }
        else if (userQuery == "goodbye") {
            response = 2; // Goodbye response
        }
        else {
            cout << "Sorry, I didn't understand that.\n";
            continue;
        }

        switch (response) {
            case 1:
                cout << "Hello! How are you doing today?\n";
                break;
            case 2:
                cout << "Goodbye! Come back soon.\n";
                break;
            default:
                cout << "Invalid query. Try again.\n";
                break;
        }
    }

    return 0;
}