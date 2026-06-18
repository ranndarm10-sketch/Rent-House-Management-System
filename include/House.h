#ifndef HOUSE_H
#define HOUSE_H

#include <string>
using namespace std;

class House {
public:
    int id;
    string address;
    double rent;
    bool available;

    House();
    House(int i, string a, double r);
};

#endif