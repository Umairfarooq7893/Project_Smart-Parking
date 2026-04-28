#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// ================= VEHICLE =================
class Vehicle {
protected:
    string number;
public:
    Vehicle(string num) { number = num; }
    virtual void display() = 0;
    string getNumber() { return number; }
};

class Car : public Vehicle {
public:
    Car(string num) : Vehicle(num) {}
    void display() { cout << "Car: " << number; }
};

class Bike : public Vehicle {
public:
    Bike(string num) : Vehicle(num) {}
    void display() { cout << "Bike: " << number; }
};

class Truck : public Vehicle {
public:
    Truck(string num) : Vehicle(num) {}
    void display() { cout << "Truck: " << number; }
};

// ================= LINKED LIST (Entry Log) =================
class Node {
public:
    string data;
    Node* next;
    Node(string d) {
        data = d;
        next = NULL;
    }
};

class EntryLog {
    Node* head;
public:
    EntryLog() { head = NULL; }

    void add(string num) {
        Node* temp = new Node(num);
        temp->next = head;
        head = temp;
    }

    void display() {
        Node* curr = head;
        cout << "Entry Log: ";
        while (curr) {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << "NULL\n";
    }
};

// ================= PARKING SLOT =================
class ParkingSlot {
public:
    int slotNumber;
    Vehicle* vehicle;

    ParkingSlot(int num) {
        slotNumber = num;
        vehicle = NULL;
    }

    bool isEmpty() { return vehicle == NULL; }

    void parkVehicle(Vehicle* v) {
        if (isEmpty()) {
            vehicle = v;
            cout << "Parked at slot " << slotNumber << endl;
        } else {
            cout << "Slot occupied!\n";
        }
    }

    string vacateSlot() {
        if (!isEmpty()) {
            string num = vehicle->getNumber();
            delete vehicle;
            vehicle = NULL;
            cout << "Slot " << slotNumber << " vacated\n";
            return num;
        }
        cout << "Already empty\n";
        return "";
    }

    void display() {
        cout << "Slot " << slotNumber << ": ";
        if (isEmpty()) cout << "Empty";
        else vehicle->display();
        cout << endl;
    }
};

// ================= MAIN =================
int main() {
    int n;
    cout << "Enter number of slots: ";
    cin >> n;

    vector<ParkingSlot> slots;
    for (int i = 1; i <= n; i++)
        slots.push_back(ParkingSlot(i));

    EntryLog log;              // Linked List
    stack<pair<int, string>> undoStack; // Stack
    queue<string> exitQueue;   // Queue

    int choice;
    do {
        cout << "\n1.Park 2.Vacate 3.Display 4.Log 5.Undo 6.ExitQueue 7.Exit\n";
        cin >> choice;

        if (choice == 1) {
            int type, slot;
            string num;

            cout << "1-Car 2-Bike 3-Truck: ";
            cin >> type;
            cout << "Number: ";
            cin >> num;
            cout << "Slot: ";
            cin >> slot;

            Vehicle* v = NULL;
            if (type == 1) v = new Car(num);
            else if (type == 2) v = new Bike(num);
            else if (type == 3) v = new Truck(num);

            if (slot >= 1 && slot <= n) {
                if (slots[slot - 1].isEmpty()) {
                    slots[slot - 1].parkVehicle(v);
                    log.add(num); // Linked List
                    undoStack.push({slot, num}); // Stack
                } else {
                    cout << "Slot occupied!\n";
                    delete v;
                }
            } else {
                cout << "Invalid slot\n";
                delete v;
            }
        }

        else if (choice == 2) {
            int slot;
            cout << "Slot to vacate: ";
            cin >> slot;

            if (slot >= 1 && slot <= n) {
                string num = slots[slot - 1].vacateSlot();
                if (num != "")
                    exitQueue.push(num); // Queue
            } else {
                cout << "Invalid slot\n";
            }
        }

        else if (choice == 3) {
            for (auto &s : slots) s.display();
        }

        else if (choice == 4) {
            log.display(); // Linked List
        }

        else if (choice == 5) {
            if (!undoStack.empty()) {
                auto last = undoStack.top();
                undoStack.pop();

                int slot = last.first;
                slots[slot - 1].vacateSlot();

                cout << "Undo last park operation\n";
            } else {
                cout << "Nothing to undo\n";
            }
        }

        else if (choice == 6) {
            cout << "Exit Queue: ";
            queue<string> temp = exitQueue;
            while (!temp.empty()) {
                cout << temp.front() << " ";
                temp.pop();
            }
            cout << endl;
        }

    } while (choice != 7);

    return 0;
}