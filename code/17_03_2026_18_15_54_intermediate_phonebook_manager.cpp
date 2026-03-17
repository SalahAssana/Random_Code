#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
};

class PhonebookManager {
public:
    PhonebookManager() : contacts_(), index_(0) {}

    void addContact(string name, string phoneNumber) {
        if (phoneNumber.empty()) {
            cout << "Error: phone number cannot be empty." << endl;
            return;
        }
        Contact contact = {name, phoneNumber};
        contacts_[name] = contact;
    }

    bool searchContact(string name) {
        if (contacts_.find(name) == contacts_.end()) {
            cout << "Error: contact not found." << endl;
            return false;
        }
        cout << "Found contact: " << contacts_[name].name << ", Phone Number: " << contacts_[name].phoneNumber << endl;
        return true;
    }

    void removeContact(string name) {
        if (contacts_.find(name) == contacts_.end()) {
            cout << "Error: contact not found." << endl;
            return;
        }
        contacts_.erase(name);
    }

private:
    unordered_map<string, Contact> contacts_;
};

int main() {
    PhonebookManager phonebook;

    phonebook.addContact("John Doe", "123-4567");
    phonebook.addContact("Jane Smith", "987-6543");

    phonebook.searchContact("John Doe");
    phonebook.searchContact("Jane Smith");
    phonebook.searchContact("Unknown Contact");

    phonebook.removeContact("Jane Smith");

    phonebook.searchContact("John Doe");
    phonebook.searchContact("Jane Smith");

    return 0;
}