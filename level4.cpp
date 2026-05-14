#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Vehicle {
protected:
    string number;

public:
    Vehicle(string num) {
        number = num;
    }

    virtual void display() = 0;

    string getNumber() {
        return number;
    }
};

class Car : public Vehicle {
public:
    Car(string num) : Vehicle(num) {}

    void display() {
        cout << "Car: " << number;
    }
};

class Bike : public Vehicle {
public:
    Bike(string num) : Vehicle(num) {}

    void display() {
        cout << "Bike: " << number;
    }
};

class Truck : public Vehicle {
public:
    Truck(string num) : Vehicle(num) {}

    void display() {
        cout << "Truck: " << number;
    }
};
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
    EntryLog() {
        head = NULL;
    }

    void add(string num) {
        Node* temp = new Node(num);
        temp->next = head;
        head = temp;
    }

    void display() {
        Node* curr = head;

        cout << "Entry Log: ";

        while (curr != NULL) {
            cout << curr->data << " -> ";
            curr = curr->next;
        }

        cout << "NULL\n";
    }
};

class AVLNode {
public:
    int slot;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int s) {
        slot = s;
        left = right = NULL;
        height = 1;
    }
};

int getHeight(AVLNode* node) {
    if (node == NULL)
        return 0;

    return node->height;
}

int getBalance(AVLNode* node) {
    if (node == NULL)
        return 0;

    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLNode* insertAVL(AVLNode* node, int slot) {

    if (node == NULL)
        return new AVLNode(slot);

    if (slot < node->slot)
        node->left = insertAVL(node->left, slot);

    else if (slot > node->slot)
        node->right = insertAVL(node->right, slot);

    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && slot < node->left->slot)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && slot > node->right->slot)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && slot > node->left->slot) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && slot < node->right->slot) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->slot << " ";
        inorder(root->right);
    }
}

priority_queue<int> availableSlots;


class ParkingSlot {
public:
    int slotNumber;
    Vehicle* vehicle;

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
            cout << "Vehicle parked at slot "
                 << slotNumber << endl;
        }
        else {
            cout << "Slot occupied\n";
        }
    }

    void vacateSlot() {
        if (!isEmpty()) {
            delete vehicle;
            vehicle = NULL;

            availableSlots.push(slotNumber);

            cout << "Slot vacated\n";
        }
        else {
            cout << "Already empty\n";
        }
    }

    void display() {
        cout << "Slot " << slotNumber << ": ";

        if (isEmpty())
            cout << "Empty";

        else
            vehicle->display();

        cout << endl;
    }
};


int main() {

    int n;

    cout << "Enter number of slots: ";
    cin >> n;

    vector<ParkingSlot> slots;

    for (int i = 1; i <= n; i++) {
        slots.push_back(ParkingSlot(i));
        availableSlots.push(i);
    }

    EntryLog log;
    stack<int> undoStack;

    AVLNode* root = NULL;

    int choice;

    do {

        cout << "\n1.Park";
        cout << "\n2.Vacate";
        cout << "\n3.Display";
        cout << "\n4.Entry Log";
        cout << "\n5.Undo";
        cout << "\n6.Display AVL";
        cout << "\n7.Best Slot";
        cout << "\n8.Exit";
        cout << "\nEnter choice: ";

        cin >> choice;


        if (choice == 1) {

            int type, slot;
            string num;

            cout << "1.Car 2.Bike 3.Truck : ";
            cin >> type;

            cout << "Enter vehicle number: ";
            cin >> num;

            cout << "Enter slot: ";
            cin >> slot;

            Vehicle* v = NULL;

            if (type == 1)
                v = new Car(num);

            else if (type == 2)
                v = new Bike(num);

            else if (type == 3)
                v = new Truck(num);

            if (slot >= 1 && slot <= n) {

                if (slots[slot - 1].isEmpty()) {

                    slots[slot - 1].parkVehicle(v);

                    log.add(num);

                    undoStack.push(slot);

                    root = insertAVL(root, slot);
                }

                else {
                    cout << "Slot occupied\n";
                }
            }

            else {
                cout << "Invalid slot\n";
            }
        }


        else if (choice == 2) {

            int slot;

            cout << "Enter slot: ";
            cin >> slot;

            if (slot >= 1 && slot <= n) {
                slots[slot - 1].vacateSlot();
            }

            else {
                cout << "Invalid slot\n";
            }
        }

        else if (choice == 3) {

            for (int i = 0; i < slots.size(); i++) {
                slots[i].display();
            }
        }


        else if (choice == 4) {

            log.display();
        }

        else if (choice == 5) {

            if (!undoStack.empty()) {

                int slot = undoStack.top();
                undoStack.pop();

                slots[slot - 1].vacateSlot();

                cout << "Undo successful\n";
            }

            else {
                cout << "Nothing to undo\n";
            }
        }
        else if (choice == 6) {

            cout << "AVL Tree (Inorder): ";
            inorder(root);
            cout << endl;
        }
        else if (choice == 7) {

            if (!availableSlots.empty()) {

                cout << "Best Available Slot: "
                     << availableSlots.top() << endl;
            }

            else {
                cout << "No slots available\n";
            }
        }

    } while (choice != 8);

    return 0;
}