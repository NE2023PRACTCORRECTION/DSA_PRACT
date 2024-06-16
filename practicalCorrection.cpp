#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to hold item information
struct Item {
    int item_id;
    string item_name;
    int item_quantity;
    string item_registration_date;
};

// Function to add item to inventory and save to CSV file
void addItem(const string& filename, int item_id, const string& item_name, int item_quantity, const string& item_registration_date) {
    ofstream file;
    file.open(filename, ios::app); // Open file in append mode
    if (file.is_open()) {
        file << item_id << "," << item_name << "," << item_quantity << "," << item_registration_date << "\n";
        file.close();
        cout << "Item added successfully." << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

// Function to read items from CSV file
vector<Item> readItems(const string& filename) {
    vector<Item> inventory;
    ifstream file(filename);
    string line;
    
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string item_id_str, item_name, item_quantity_str, item_registration_date;
            if (getline(ss, item_id_str, ',') &&
                getline(ss, item_name, ',') &&
                getline(ss, item_quantity_str, ',') &&
                getline(ss, item_registration_date)) {
                Item item = {stoi(item_id_str), item_name, stoi(item_quantity_str), item_registration_date};
                inventory.push_back(item);
            }
        }
        file.close();
    } else {
        cout << "Unable to open file for reading." << endl;
    }
    return inventory;
}

// Function to list items in inventory in alphabetical order
void listItems(const string& filename) {
    vector<Item> inventory = readItems(filename);
    if (inventory.empty()) {
        cout << "Inventory is empty." << endl;
        return;
    }

    sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
        return a.item_name < b.item_name;
    });

    for (const auto& item : inventory) {
        cout << "Item id: " << item.item_id << "  "
             << "Item name: " << item.item_name << "  "
             << "Quantity: " << item.item_quantity << "  "
             << "Reg Date: " << item.item_registration_date << endl;
    }
}

// Function to display help message
void displayHelp() {
    cout << "Available commands:" << endl;
    cout << " - itemadd <item_id>,<item_name>,<item_quantity>,<item_registration_date>: Add new item to inventory." << endl;
    cout << " - itemslist: List items in inventory in alphabetical order." << endl;
    cout << " - help: Display this help message." << endl;
    cout << " - exit: Exit the program." << endl;
}

void processCommands() {
    const string filename = "inventory.csv";
    string command;
    while (true) {
        cout << "Enter command: ";
        getline(cin, command);

        // Convert command to lowercase for case-insensitive comparison
        transform(command.begin(), command.end(), command.begin(), ::tolower);

        stringstream ss(command);
        string cmd; 
        ss >> cmd;

        if (cmd == "itemadd") {
            string input;
            getline(ss, input);
            replace(input.begin(), input.end(), ',', ' '); // Replace commas with spaces
            stringstream input_ss(input);

            int item_id, item_quantity;
            string item_name, item_registration_date;
            // Read inputs
            if (!(input_ss >> item_id >> item_name >> item_quantity >> item_registration_date)) {
                cout << "Invalid input format. Usage: itemadd <item_id>,<item_name>,<item_quantity>,<item_registration_date>" << endl;
                continue;
            }
            addItem(filename, item_id, item_name, item_quantity, item_registration_date);
        } else if (cmd == "itemslist") {
            listItems(filename);
        } else if (cmd == "help") {
            displayHelp();
        } else if (cmd == "exit") {
            cout << "Exiting program..." << endl;
            break;
        } else {
            cout << "Invalid command. Type 'help' for list of commands." << endl;
        }
    }
}

int main() {
    cout << " ==================================================== " << endl;
    cout << "*     Welcome to INVENTORY MANAGEMENT SYSTEM!        *" << endl;
    cout << "*  ***********************************************  *" << endl;
    cout << "*                                                    *" << endl;
    cout << "* It is developed by 'OXANE' as practical evaluation *" << endl;
    cout << "* for the end of Year 3.                             *" << endl;
    cout << " ==================================================== " << endl;
    cout << "Starting Time: Mon May 29 22:35:00 CAT 2023" << endl;
    cout << " ==================================================== " << endl;

    processCommands();
    return 0;
}
