#ifndef TENANT_H
#define TENANT_H

#include <string>
using namespace std;

class Tenant {
public:
    int id;
    string name;
    string phone;

    Tenant();
    Tenant(int i, string n, string p);
};

#endif