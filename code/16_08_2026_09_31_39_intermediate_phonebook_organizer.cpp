#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Struct to represent a contact
struct Contact {
    std::string name;
    std::string phone;
};

// Function to sort contacts based on their names
bool compareContacts(const Contact& c1, const Contact& c2) {
    return c1.name < c2.name;
}

// Class to manage the phonebook
class Phonebook {
private:
    std::vector<Contact> contacts;

public:
    // Add a new contact to the phonebook
    void addContact(std::string name, std::string phone) {
        Contact contact = {name, phone};
        contacts.push_back(contact);
        std::sort(contacts.begin(), contacts.end(), compareContacts);
    }

    // Search for a contact by name and return its phone number
    std::string searchContact(const std::string& name) {
        for (const auto& contact : contacts) {
            if (contact.name == name) {
                return contact.phone;
            }
        }
        return "Contact not found";
    }

    // Remove a contact from the phonebook by name
    void removeContact(const std::string& name) {
        contacts.erase(std::remove_if(contacts.begin(), contacts.end(),
                                       [&](const Contact& c) { return c.name == name; }), contacts.end());
    }
};

int main() {
    Phonebook phonebook;

    // Add some initial contacts
    phonebook.addContact("John", "123-4567");
    phonebook.addContact("Jane", "901-2345");
    phonebook.addContact("Bob", "567-8901");

    // Search for a contact
    std::cout << "Phone number of John: " << phonebook.searchContact("John") << std::endl;

    // Remove a contact
    phonebook.removeContact("Jane");

    return 0;
}