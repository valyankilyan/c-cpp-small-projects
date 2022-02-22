#include "../include/triangle.h"

#include <iostream>

bool Triangle::is_done() {
    return size() == 3;
}

bool Triangle::validate() {
    cout << "Triangle validation\n";
    if (size() > 3) {
        return 0;
    }
    return Polygon::validate();
}