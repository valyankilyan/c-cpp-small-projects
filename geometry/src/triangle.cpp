#include "../include/triangle.h"

#include <iostream>

Triangle::Triangle() {}

Triangle::Triangle(Line* l) {
    cords = vector<Point>();
    for (size_t i = 0; i < min(l->size(), (size_t)4); i++) {
        push_back(l->operator[](i));
    }
}

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