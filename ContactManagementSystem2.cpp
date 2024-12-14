#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

void addContact();
void viewContacts();
void editContact();
void deleteContact();
void saveContacts(const vector<Contact>& contacts);
vector<Contact> loadContacts();

int main() {
    int choice;

    do {
        cout << "\n--- Contact Management System ---\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                editContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

void addContact() {
    Contact newContact;
    cout << "Enter Name: ";
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, newContact.name);
    cout << "Enter Phone Number: ";
    getline(cin, newContact.phone);
    cout << "Enter Email Address: ";
    getline(cin, newContact.email);

    vector<Contact> contacts = loadContacts();
    contacts.push_back(newContact);
    saveContacts(contacts);

    cout << "Contact added successfully!" << endl;
}

void viewContacts() {
    vector<Contact> contacts = loadContacts();
    cout << "\n--- Contact List ---\n";
    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << i + 1 << ". Name: " << contacts[i].name
             << ", Phone: " << contacts[i].phone
             << ", Email: " << contacts[i].email << endl;
    }
}

void editContact() {
    vector<Contact> contacts = loadContacts();
    viewContacts();

    int index;
    cout << "Enter the number of the contact to edit: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number." << endl;
        return;
    }

    Contact& contact = contacts[index - 1];
    cout << "Editing Contact: " << contact.name << endl;
    cout << "Enter new Name (leave blank to keep current): ";
    cin.ignore();
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        contact.name = newName;
    }

    cout << "Enter new Phone Number (leave blank to keep current): ";
    string newPhone;
    getline(cin, newPhone);
    if (!newPhone.empty()) {
        contact.phone = newPhone;
    }

    cout << "Enter new Email Address (leave blank to keep current): ";
    string newEmail;
    getline(cin, newEmail);
    if (!newEmail.empty()) {
        contact.email = newEmail;
    }

    saveContacts(contacts);
    cout << "Contact updated successfully!" << endl;
}

void deleteContact() {
    vector<Contact> contacts = loadContacts();
    viewContacts();

    int index;
    cout << "Enter the number of the contact to delete: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number." << endl;
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    saveContacts(contacts);
    cout << "Contact deleted successfully!" << endl;
}

void saveContacts(const vector<Contact>& contacts) {
    ofstream file("contacts.txt");
    for (const auto& contact : contacts) {
        file << contact.name << "\n" << contact.phone << "\n" << contact.email << "\n";
    }
}

vector<Contact> loadContacts() {
    vector<Contact> contacts;
    ifstream file("contacts.txt");
    Contact contact;

    while (getline(file, contact.name) && getline(file, contact.phone) && getline(file, contact.email)) {
        contacts.push_back(contact);
    }

    return contacts;
}