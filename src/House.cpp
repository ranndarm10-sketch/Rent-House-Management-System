#include "House.h"

House::House() {
    id = 0;
    address = "";
    rent = 0;
    available = true;
}

House::House(int i, string a, double r) {
    id = i;
    address = a;
    rent = r;
    available = true;
}