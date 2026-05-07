#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <cstring>
using namespace std;

// ================= VEHICLE =================
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

// ================= LINKED LIST =================
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

// ================= AVL TREE =================
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
    return node == NULL ? 0 : node->height;
}

int getBalance(AVLNode* node) {
    return node == NULL ? 0 :
           getHeight(node->left) - getHeight(node->right);
}

AVLNode* rightRotate(AVLNode* y) {

    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height =
        max(getHeight(y->left), getHeight(y->right)) + 1;

    x->height =
        max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {

    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height =
        max(getHeight(x->left), getHeight(x->right)) + 1;

    y->height =
        max(getHeight(y->left), getHeight(y->right)) + 1;

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

    node->height =
        max(getHeight(node->left),
            getHeight(node->right)) + 1;

    int balance = getBalance(node);

    // LL
    if (balance > 1 && slot < node->left->slot)
        return rightRotate(node);

    // RR
    if (balance < -1 && slot > node->right->slot)
        return leftRotate(node);

    // LR
    if (balance > 1 && slot > node->left->slot) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
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

// ================= HEAP =================
priority_queue<int> availableSlots;

// ================= HASH TABLE =================
unordered_map<string, int> vehicleMap;

// ================= GRAPH =================
vector<int> graph[100];

// BFS
void bfs(int start, int destination, int n) {

    vector<bool> visited(n + 1, false);

    queue<int> q;

    q.push(start);

    visited[start] = true;

    cout << "Navigation Path: ";

    while (!q.empty()) {

        int node = q.front();
        q.pop();

        cout << node << " ";

        if (node == destination) {
            cout << endl;
            return;
        }

        for (int next : graph[node]) {

            if (!visited[next]) {

                visited[next] = true;
                q.push(next);
            }
        }
    }

    cout << "\nNo path found\n";
}

// ================= KMP =================
bool KMPSearch(string text, string pattern) {

    int n = text.length();
    int m = pattern.length();

    int lps[m];

    lps[0] = 0;

    int len = 0;
    int i = 1;

    while (i < m) {

        if (pattern[i] == pattern[len]) {

            len++;
            lps[i] = len;
            i++;
        }

        else {

            if (len != 0)
                len = lps[len - 1];

            else {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0;
    int j = 0;

    while (i < n) {

        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m)
            return true;

        else if (i < n && pattern[j] != text[i]) {

            if (j != 0)
                j = lps[j - 1];

            else
                i++;
        }
    }

    return false;
}

// ================= PARKING SLOT =================
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

            vehicleMap[v->getNumber()] = slotNumber;

            cout << "Vehicle parked at slot "
                 << slotNumber << endl;
        }

        else {
            cout << "Slot occupied\n";
        }
    }

    void vacateSlot() {

        if (!isEmpty()) {

            vehicleMap.erase(vehicle->getNumber());

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

// ================= MAIN =================
int main() {

    int n;

    cout << "Enter number of slots: ";
    cin >> n;

    vector<ParkingSlot> slots;

    for (int i = 1; i <= n; i++) {

        slots.push_back(ParkingSlot(i));

        availableSlots.push(i);
    }

    // Create simple graph connections
    for (int i = 1; i < n; i++) {

        graph[i].push_back(i + 1);
        graph[i + 1].push_back(i);
    }

    EntryLog log;

    stack<int> undoStack;

    AVLNode* root = NULL;

    int choice;

    do {

        cout << "\n===== SMART PARKING =====\n";

        cout << "1. Park Vehicle\n";
        cout << "2. Vacate Slot\n";
        cout << "3. Display Slots\n";
        cout << "4. Entry Log\n";
        cout << "5. Undo Parking\n";
        cout << "6. AVL Display\n";
        cout << "7. Best Slot\n";
        cout << "8. Find Vehicle\n";
        cout << "9. License Pattern Search\n";
        cout << "10. Navigation BFS\n";
        cout << "11. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        // ================= PARK =================
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

        // ================= VACATE =================
        else if (choice == 2) {

            int slot;

            cout << "Enter slot: ";
            cin >> slot;

            if (slot >= 1 && slot <= n)
                slots[slot - 1].vacateSlot();

            else
                cout << "Invalid slot\n";
        }

        // ================= DISPLAY =================
        else if (choice == 3) {

            for (int i = 0; i < slots.size(); i++) {
                slots[i].display();
            }
        }

        // ================= LOG =================
        else if (choice == 4) {

            log.display();
        }

        // ================= UNDO =================
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

        // ================= AVL =================
        else if (choice == 6) {

            cout << "AVL Tree: ";

            inorder(root);

            cout << endl;
        }

        // ================= HEAP =================
        else if (choice == 7) {

            if (!availableSlots.empty()) {

                cout << "Best Available Slot: "
                     << availableSlots.top() << endl;
            }

            else {
                cout << "No slots available\n";
            }
        }

        // ================= HASH =================
        else if (choice == 8) {

            string num;

            cout << "Enter vehicle number: ";
            cin >> num;

            if (vehicleMap.find(num) != vehicleMap.end()) {

                cout << "Vehicle found at slot "
                     << vehicleMap[num] << endl;
            }

            else {
                cout << "Vehicle not found\n";
            }
        }

        // ================= KMP =================
        else if (choice == 9) {

            string pattern;

            cout << "Enter pattern: ";
            cin >> pattern;

            bool found = false;

            for (auto x : vehicleMap) {

                if (KMPSearch(x.first, pattern)) {

                    cout << "Matched Vehicle: "
                         << x.first << endl;

                    found = true;
                }
            }

            if (!found)
                cout << "No matching vehicle\n";
        }

        // ================= BFS =================
        else if (choice == 10) {

            int start, destination;

            cout << "Enter start slot: ";
            cin >> start;

            cout << "Enter destination slot: ";
            cin >> destination;

            bfs(start, destination, n);
        }

    } while (choice != 11);

    return 0;
}