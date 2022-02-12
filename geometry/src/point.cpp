#include "../include/point.h"

#include <iostream>
#include <utility>
using namespace std;

Point::Point(int x, int y) {
    this->dimensions = 2;
    this->cords = new int[dimensions];
    this->cords[0] = x;
    this->cords[1] = y;
}

Point::~Point() {
    delete[] cords;
}

void Point::set(int x, int y) {
    this->cords[0] = x;
    this->cords[1] = y;
}

pair<int, int> Point::get() {
    return make_pair(this->cords[0], this->cords[1]);
}

void Point::print() {
    cout << "(";
    for (int i = 0; i < this->dimensions - 1; i++) {
        cout << this->cords[i] << ", ";
    }
    cout << this->cords[dimensions - 1] << ")";
}

ostream& operator<<(ostream& os, const Point& p) {
    os << "(";
    for (int i = 0; i < p.dimensions - 1; i++) {
        os << p.cords[i] << ", ";
    }
    os << p.cords[p.dimensions - 1] << ")";
    return os;
}