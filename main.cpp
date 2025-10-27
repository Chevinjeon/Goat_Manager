#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
void display_goat_menu(list<Goat> trip);

int main() {
    srand(time(0));

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    list<Goat> trip;
    bool again = true;

    while (again) {
        int choice = main_menu();
        switch(choice) {
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                again = false;
                cout << "\nThanks for using Goat Manager 3001!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}

// Task 2: Display main menu and get user choice
int main_menu() {
    cout << "\n*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    return choice;
}

// Display the goat selection submenu
void display_goat_menu(list<Goat> trip) {
    int index = 1;
    for (const Goat& g : trip) {
        cout << "    [" << index << "] " << g.get_name() 
             << " (" << g.get_age() << ", " << g.get_color() << ")\n";
        index++;
    }
}

// Task 3: Add a goat to the trip
void add_goat(list<Goat> &trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % (MAX_AGE + 1);
    
    Goat newGoat(name, age, color);
    trip.push_back(newGoat);
    cout << "\nAdded: " << name << " (" << age << ", " << color << ")\n";
    trip.sort();
}

// Task 3: Delete a goat from the trip
void delete_goat(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "\nNo goats to delete.\n";
        return;
    }
    
    display_goat_menu(trip);
    cout << "\nWhich goat to delete? --> ";
    int choice;
    cin >> choice;
    
    if (choice >= 1 && choice <= (int)trip.size()) {
        auto it = trip.begin();
        for (int i = 1; i < choice; i++) {
            it++;
        }
        cout << "\nDeleted: " << it->get_name() << " (" 
             << it->get_age() << ", " << it->get_color() << ")\n";
        trip.erase(it);
    } else {
        cout << "Invalid choice.\n";
    }
}

// Task 3: Display all goats in the trip
void display_trip(list<Goat> trip) {
    if (trip.empty()) {
        cout << "\nNo goats on the trip.\n";
        return;
    }
    
    cout << "\n*** Current Trip ***\n";
    display_goat_menu(trip);
}
