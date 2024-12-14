#include <iostream>
#include <fstream>
#include <cstdlib>  // For exit()
#include <string>   // For string
using namespace std;

// Global variables
string fname, lname, phone_num;

// Functions
void addContact();
void searchContact();
void help();
void self_exit();
bool check_digits(string);
bool check_numbers(string);

int main() {
    short int choice;
    system("cls");
    system("color 0A");
    cout << "\n\n\t*******CONTACT MANAGEMENT SYSTEM******* \n";
    cout << "\n\n\t 1. Add Contact\n\t 2. Search Contact\n\t 3. Help\n\t 4. Exit\n >";
    cin >> choice;

    switch (choice) {
        case 1:
            addContact();
            break;
        case 2:
            searchContact();
            break;
        case 3:
            help();
            break;
        case 4:
            self_exit();
            break;
        default:
            cout << "\n\n\tInvalid Input:";
            cout << "\n\tPress any key to Continue..."; 
            system("pause");
            main();
    }
    return 0;
}

void self_exit() { 
    system("cls");
    cout << "\n\n\n\tTHANK YOU FOR USING !!" << endl;
    exit(1);
}

void help() {
    cout << "This displays Help!" << endl;
}

void addContact() {
    ofstream phone("number.txt", ios::app);
    system("cls");
    cout << "\n\n\tEnter First Name: ";
    cin >> fname;
    cout << "\n\n\tEnter Last Name: ";
    cin >> lname;
    cout << "\n\n\tEnter 10-digit Phone Number: ";
    cin >> phone_num;

    if (check_digits(phone_num)) {
        if (check_numbers(phone_num)) {
            if (phone.is_open()) {
                phone << fname << " " << lname << " " << phone_num << endl;
                cout << "\n\tContact saved Successfully!" << endl;
            } else {
                cout << "\n\tError In Opening File!" << endl;
            }
        } else {
            cout << "\n\tA Phone Number Must Contain Only Numbers!!" << endl;
        }
    } else {
        cout << "\n\tA Phone Number must contain 10 digits" << endl;
    }
    phone.close();
}

void searchContact() {
    bool found = false;
    ifstream myFile("number.txt");
    string keyword;
    cout << "\n\tEnter Name To Search: " << endl;
    cin >> keyword;
    while (myFile >> fname >> lname >> phone_num) {
        if (keyword == fname || keyword == lname) {
            system("cls");
            cout << "\n\n\n\t\tContact Details: ";
            cout << "\n\n\tFirst Name: " << fname;
            cout << "\n\tLast Name: " << lname;
            cout << "\n\tPhone Number: " << phone_num << endl;
            found = true;
            break;
        }  
    }
    if (!found) {
        cout << "\n\tNo such Contact Found!" << endl;
    }
    myFile.close();
}

bool check_digits(string x) {
    return x.length() == 10;
}

bool check_numbers(string x) {
    for (char c : x) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}