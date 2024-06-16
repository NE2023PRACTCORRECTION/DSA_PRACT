#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

void addLocation(string &location) {
    ofstream file("location.csv", ios::app);
    if (file.is_open()) {
        file << "location :" << location << endl;
        file.close();
        cout << "Location added successfully.\n";
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

void deleteLocation(const string& location) {
    ifstream inFile("location.csv");
    if (!inFile) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    ofstream outFile("temp.csv");
    if (!outFile) {
        cout << "Error: Unable to create temporary file." << endl;
        inFile.close();
        return;
    }

    string line;
    bool locationFound = false;
    string locationPrefix = "location :" + location;

    while (getline(inFile, line)) {
        if (line != locationPrefix) {
            outFile << line << endl;
        } else {
            locationFound = true;
        }
    }

    inFile.close();
    outFile.close();

    if (locationFound) {
        remove("location.csv");
        rename("temp.csv", "location.csv");
        cout << "Location deleted successfully." << endl;
    } else {
        remove("temp.csv");
        cout << "Location not found." << endl;
    }
}

void listLocations() {
    ifstream file("location.csv");
    string location;
    if (!file.is_open()) {
        cout << "Unable to open file" << endl;
        return;
    }
    while (getline(file, location)) {
        cout << location << endl;
    }
    file.close();
}

void help() {
    cout << " ============================================================================" << endl;
    cout << " *                                   HELP MENU                              *" << endl;
    cout << " ===========================================================================" << endl;
    cout << " add <location>                          : Add a new location" << endl;
    cout << " delete <location>                       : Delete an existing location" << endl;
    cout << " list locations                          : List all existing locations" << endl;
    cout << " help                                    : Display this help message" << endl;
    cout << " exit                                    : Exit the program" << endl;
    cout << " =============================================================================" << endl;
}

void processCommands() {
    string cont = "yes";
    while (cont != "exit" && cont != "no") {
        string command1;
        string location;
        cout << "Please enter the command (add, delete, list, help, exit): ";
        cin >> command1;
        transform(command1.begin(), command1.end(), command1.begin(), ::tolower);

        if (command1 == "add") {
            cout << "Enter location: ";
            cin >> location;
            addLocation(location);
        } else if (command1 == "delete") {
            cout << "Enter location: ";
            cin >> location;
            deleteLocation(location);
        } else if (command1 == "list") {
            listLocations();
        } else if (command1 == "help") {
            help();
        } else if (command1 == "exit") {
            break;
        } else {
            cout << "The command was incorrect.\n";
        }

        cout << "Do you want to continue (yes/no): ";
        cin >> cont;
        transform(cont.begin(), cont.end(), cont.begin(), ::tolower);
    }
}

int main() {
    cout << " ==================================================== " << endl;
    cout << "*     Welcome to Location Reporting System!     *" << endl;
    cout << "*  **************************************** *" << endl;
    cout << "*                           *" << endl;
    cout << "* It is developed by 'OXANE' as practical *" << endl;
    cout << "* evaluation for the end of Year 3.               *" << endl;
    cout << " ====================================================" << endl;
    cout << "Starting Time: Mon May 29 22:35:00 CAT 2023" << endl;
    cout << " ====================================================" << endl;

    processCommands();
    return 0;
}
