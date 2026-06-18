#include "Tenant.h"

Tenant::Tenant() {
    id = 0;
    name = "";
    phone = "";
}

Tenant::Tenant(int i, string n, string p) {
    id = i;
    name = n;
    phone = p;
}