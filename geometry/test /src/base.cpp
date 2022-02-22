#include "../include/base.h"

#include <iostream>

Base::Base() {}

void Base::print() {
    cout << "Name of this class is: ";
    name();
    cout << endl;
}

void Base::name() {
    cout << "Base";
}