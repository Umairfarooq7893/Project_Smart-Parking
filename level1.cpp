/*
    Author :  Umair Farooq
    program : Parking Lot Management System
*/
#include <iostream>
#include <vector>
using namespace std;

// Abstract Class
class Vehicle {
protected:
    string number;
public:
    Vehicle(string num) {
        number = num;
    }
    virtual void display() = 0; // pure virtual function
    string getNumber() {
        return number;
    }
};

// Derived Classes
class Car : public Vehicle {
public:
    Car(string num) : Vehicle(num) {}
    void display() {
        cout << "Car Number: " << number << endl;
    }
};

class Bike : public Vehicle {
public:
    Bike(string num) : Vehicle(num) {}
    void display() {
        cout << "Bike Number: " << number << endl;
    }
};

class Truck : public Vehicle {
public:
    Truck(string num) : Vehicle(num) {}
    void display() {
        cout << "Truck Number: " << number << endl;
    }
};

// Parking Slot Class
class ParkingSlot {
    int slotNumber;
    Vehicle* vehicle;

public:
    ParkingSlot(int num) {
        slotNumber = num;
        vehicle = NULL;
    }

    bool isEmpty() {
        return vehicle == NULL;
    }

    void parkVehicle(Vehicle* v) {
        if (isEmpty()) {
            vehicle = v;
            cout << "Vehicle parked in slot " << slotNumber << endl;
        } else {
            cout << "Slot already occupied!" << endl;
        }
    }

    void vacateSlot() {
        if (!isEmpty()) {
            cout << "Slot " << slotNumber << " vacated\n";
            delete vehicle;
            vehicle = NULL;
        } else {
            cout << "Slot already empty!\n";
        }
    }

    void displayStatus() {
        cout << "Slot " << slotNumber << ": ";
        if (isEmpty()) {
            cout << "Empty\n";
        } else {
            vehicle->display();
        }
    }
};

// Main Function
int main() {
    int n;
    cout << "Enter number of parking slots: ";
    cin >> n;

    vector<ParkingSlot> slots;
    for (int i = 1; i <= n; i++) {
        slots.push_back(ParkingSlot(i));
    }

    int choice;
    do {
        cout << "\n1. Park Vehicle\n2. Vacate Slot\n3. Display Status\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int type, slot;
            string number;

            cout << "Enter vehicle type (1-Car, 2-Bike, 3-Truck): ";
            cin >> type;
            cout << "Enter vehicle number: ";
            cin >> number;
            cout << "Enter slot number: ";
            cin >> slot;

            Vehicle* v = NULL;

            if (type == 1) v = new Car(number);
            else if (type == 2) v = new Bike(number);
            else if (type == 3) v = new Truck(number);
            else {
                cout << "Invalid type!\n";
                continue;
            }

            if (slot >= 1 && slot <= n) {
                slots[slot - 1].parkVehicle(v);
            } else {
                cout << "Invalid slot number!\n";
            }

        } else if (choice == 2) {
            int slot;
            cout << "Enter slot number to vacate: ";
            cin >> slot;

            if (slot >= 1 && slot <= n) {
                slots[slot - 1].vacateSlot();
            } else {
                cout << "Invalid slot number!\n";
            }

        } else if (choice == 3) {
            for (int i = 0; i < n; i++) {
                slots[i].displayStatus();
            }
        }

    } while (choice != 4);

    return 0;
}