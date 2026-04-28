#include <iostream>
#include <vector>
using namespace std;

// vehicle class
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

// PARKING SLOT
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

    void vacateSlot() {
        if (!isEmpty()) {
            delete vehicle;
            vehicle = NULL;
            cout << "Slot " << slotNumber << " vacated\n";
        } else {
            cout << "Already empty\n";
        }
    }

    void display() {
        cout << "Slot " << slotNumber << ": ";
        if (isEmpty()) cout << "Empty";
        else vehicle->display();
        cout << endl;
    }
};


// Selection Sort (by slot number)
void selectionSort(vector<ParkingSlot>& slots) {
    int n = slots.size();
    int comparisons = 0;

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (slots[j].slotNumber < slots[minIdx].slotNumber) {
                minIdx = j;
            }
        }
        swap(slots[i], slots[minIdx]);
    }

    cout << "Selection Sort done. Comparisons: " << comparisons << endl;
}

// Insertion Sort (by vehicle number)
void insertionSort(vector<ParkingSlot>& slots) {
    int comparisons = 0;

    for (int i = 1; i < slots.size(); i++) {
        ParkingSlot key = slots[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++;
            string curr = slots[j].vehicle ? slots[j].vehicle->getNumber() : "";
            string keyVal = key.vehicle ? key.vehicle->getNumber() : "";

            if (curr > keyVal) {
                slots[j + 1] = slots[j];
                j--;
            } else break;
        }
        slots[j + 1] = key;
    }

    cout << "Insertion Sort done. Comparisons: " << comparisons << endl;
}

// Merge function for Merge Sort
void merge(vector<ParkingSlot>& slots, int l, int m, int r, int &comp) {
    vector<ParkingSlot> temp;
    int i = l, j = m + 1;

    while (i <= m && j <= r) {
        comp++;
        string a = slots[i].vehicle ? slots[i].vehicle->getNumber() : "";
        string b = slots[j].vehicle ? slots[j].vehicle->getNumber() : "";

        if (a < b) temp.push_back(slots[i++]);
        else temp.push_back(slots[j++]);
    }

    while (i <= m) temp.push_back(slots[i++]);
    while (j <= r) temp.push_back(slots[j++]);

    for (int k = 0; k < temp.size(); k++) {
        slots[l + k] = temp[k];
    }
}

// Merge Sort (by vehicle number)
void mergeSort(vector<ParkingSlot>& slots, int l, int r, int &comp) {
    if (l >= r) return;

    int mid = (l + r) / 2;
    mergeSort(slots, l, mid, comp);
    mergeSort(slots, mid + 1, r, comp);
    merge(slots, l, mid, r, comp);
}

// MAIN
int main() {
    int n;
    cout << "Enter number of slots: ";
    cin >> n;

    vector<ParkingSlot> slots;
    for (int i = 1; i <= n; i++) {
        slots.push_back(ParkingSlot(i));
    }

    int choice;
    do {
        cout << "\n1.Park 2.Vacate 3.Display 4.SelectionSort 5.InsertionSort 6.MergeSort 7.Exit\n";
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

            if (slot >= 1 && slot <= n)
                slots[slot - 1].parkVehicle(v);
            else
                cout << "Invalid slot\n";
        }

        else if (choice == 2) {
            int slot;
            cout << "Slot to vacate: ";
            cin >> slot;

            if (slot >= 1 && slot <= n)
                slots[slot - 1].vacateSlot();
            else
                cout << "Invalid slot\n";
        }

        else if (choice == 3) {
            for (auto &s : slots) s.display();
        }

        else if (choice == 4) {
            selectionSort(slots);
        }

        else if (choice == 5) {
            insertionSort(slots);
        }

        else if (choice == 6) {
            int comp = 0;
            mergeSort(slots, 0, slots.size() - 1, comp);
            cout << "Merge Sort done. Comparisons: " << comp << endl;
        }

    } while (choice != 7);

    return 0;
}