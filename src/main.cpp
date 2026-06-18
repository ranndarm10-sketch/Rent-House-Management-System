#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

/* ================= CLASSES ================= */

class House {
public:
    int id;
    string address;
    double rent;
    bool available;

    House() {}

    House(int i, string a, double r) {
        id = i;
        address = a;
        rent = r;
        available = true;
    }
};

class Tenant {
public:
    int id;
    string name;
    string phone;

    Tenant() {}

    Tenant(int i, string n, string p) {
        id = i;
        name = n;
        phone = p;
    }
};

class Rental {
public:
    int houseId;
    int tenantId;

    Rental(int h, int t) {
        houseId = h;
        tenantId = t;
    }
};

/* ================= DATA ================= */

vector<House> houses;
vector<Tenant> tenants;
vector<Rental> rentals;

/* ================= FILE SYSTEM ================= */

void saveHouses() {
    ofstream file("../data/houses.txt");
    for (auto& h : houses)
        file << h.id << "," << h.address << "," << h.rent << "," << h.available << "\n";
}

void loadHouses() {
    ifstream file("../data/houses.txt");
    if (!file) return;

    houses.clear();
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, addr, rent, avail;

        getline(ss, id, ',');
        getline(ss, addr, ',');
        getline(ss, rent, ',');
        getline(ss, avail, ',');

        House h(stoi(id), addr, stod(rent));
        h.available = stoi(avail);
        houses.push_back(h);
    }
}

void saveTenants() {
    ofstream file("../data/tenants.txt");
    for (auto& t : tenants)
        file << t.id << "," << t.name << "," << t.phone << "\n";
}

void loadTenants() {
    ifstream file("../data/tenants.txt");
    if (!file) return;

    tenants.clear();
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, phone;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');

        tenants.push_back(Tenant(stoi(id), name, phone));
    }
}

void saveRentals() {
    ofstream file("../data/rentals.txt");
    for (auto& r : rentals)
        file << r.houseId << "," << r.tenantId << "\n";
}

void loadRentals() {
    ifstream file("../data/rentals.txt");
    if (!file) return;

    rentals.clear();
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string h, t;

        getline(ss, h, ',');
        getline(ss, t, ',');

        rentals.push_back(Rental(stoi(h), stoi(t)));
    }
}

/* ================= HOUSE ================= */

void addHouse() {
    int id;
    string address;
    double rent;

    cout << "ID: ";
    cin >> id;
    cin.ignore();

    cout << "Address: ";
    getline(cin, address);

    cout << "Rent: ";
    cin >> rent;

    houses.push_back(House(id, address, rent));
    saveHouses();

    cout << "House added!\n";
}

void viewHouses() {
    cout << "\n===== HOUSE LIST =====\n";

    int no = 1;

    for (auto& h : houses) {
        cout << "No: " << no++
            << " | ID: " << h.id
            << " | Address: " << h.address
            << " | Rent: " << h.rent
            << " | " << (h.available ? "Available" : "Occupied")
            << endl;
    }
}

void editHouse() {
    int id;
    cout << "Enter House ID to edit: ";
    cin >> id;
    cin.ignore();

    for (auto& h : houses) {
        if (h.id == id) {
            cout << "New Address: ";
            getline(cin, h.address);

            cout << "New Rent: ";
            cin >> h.rent;

            saveHouses();
            cout << "House updated!\n";
            return;
        }
    }

    cout << "House not found!\n";
}

void deleteHouse() {
    int id;
    cout << "Enter House ID to delete: ";
    cin >> id;

    houses.erase(remove_if(houses.begin(), houses.end(),
        [&](House h) { return h.id == id; }), houses.end());

    saveHouses();
    cout << "House deleted!\n";
}

/* ================= TENANT ================= */

void addTenant() {
    int id;
    string name, phone;

    cout << "ID: ";
    cin >> id;
    cin.ignore();

    cout << "Name: ";
    getline(cin, name);

    cout << "Phone: ";
    getline(cin, phone);

    tenants.push_back(Tenant(id, name, phone));
    saveTenants();

    cout << "Tenant added!\n";
}

void viewTenants() {
    cout << "\n===== TENANT LIST =====\n";

    int no = 1;

    for (auto& t : tenants) {
        cout << "No: " << no++
            << " | ID: " << t.id
            << " | Name: " << t.name
            << " | Phone: " << t.phone
            << endl;
    }
}

void editTenant() {
    int id;
    cout << "Enter Tenant ID to edit: ";
    cin >> id;
    cin.ignore();

    for (auto& t : tenants) {
        if (t.id == id) {
            cout << "New Name: ";
            getline(cin, t.name);

            cout << "New Phone: ";
            getline(cin, t.phone);

            saveTenants();
            cout << "Tenant updated!\n";
            return;
        }
    }

    cout << "Tenant not found!\n";
}

void deleteTenant() {
    int id;
    cout << "Enter Tenant ID to delete: ";
    cin >> id;

    tenants.erase(remove_if(tenants.begin(), tenants.end(),
        [&](Tenant t) { return t.id == id; }), tenants.end());

    saveTenants();
    cout << "Tenant deleted!\n";
}

/* ================= RENT SYSTEM ================= */

void rentHouse() {
    int hid, tid;

    cout << "House ID: ";
    cin >> hid;

    cout << "Tenant ID: ";
    cin >> tid;

    for (auto& h : houses) {
        if (h.id == hid && h.available) {
            h.available = false;
            rentals.push_back(Rental(hid, tid));

            saveHouses();
            saveRentals();

            cout << "House rented!\n";
            return;
        }
    }

    cout << "Not available!\n";
}

void returnHouse() {
    int hid;

    cout << "House ID: ";
    cin >> hid;

    for (auto& h : houses)
        if (h.id == hid)
            h.available = true;

    rentals.erase(remove_if(rentals.begin(), rentals.end(),
        [&](Rental r) { return r.houseId == hid; }), rentals.end());

    saveHouses();
    saveRentals();

    cout << "House returned!\n";
}

/* ================= MAIN ================= */

int main() {
    loadHouses();
    loadTenants();
    loadRentals();

    int choice;

    do {
        cout << "\n===== RENT HOUSE SYSTEM =====\n";
        cout << "1. Add House\n";
        cout << "2. View Houses\n";
        cout << "3. Edit House\n";
        cout << "4. Delete House\n";
        cout << "5. Add Tenant\n";
        cout << "6. View Tenants\n";
        cout << "7. Edit Tenant\n";
        cout << "8. Delete Tenant\n";
        cout << "9. Rent House\n";
        cout << "10. Return House\n";
        cout << "11. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addHouse(); break;
        case 2: viewHouses(); break;
        case 3: editHouse(); break;
        case 4: deleteHouse(); break;
        case 5: addTenant(); break;
        case 6: viewTenants(); break;
        case 7: editTenant(); break;
        case 8: deleteTenant(); break;
        case 9: rentHouse(); break;
        case 10: returnHouse(); break;
        }

    } while (choice != 11);

    return 0;
}