#include "../include/point.h"

#include <iostream>
#include <utility>
using namespace std;

Point::Point(long double x, long double y) {
    this->dimensions = 2;
    this->cords = new long double[dimensions];
    this->cords[0] = x;
    this->cords[1] = y;
}

Point::Point() {
    this->dimensions = 2;
    this->cords = new long double[this->dimensions];
}

Point::~Point() {
    delete[] cords;
}

void Point::set(long double x, long double y) {
    this->cords[0] = x;
    this->cords[1] = y;
}

pair<long double, long double> Point::get() {
    return make_pair(this->cords[0], this->cords[1]);
}

Point Point::operator+(const Point& b) {
    Point temp = Point();
    for (int i = 0; i < dimensions; i++) {
        temp.cords[i] = cords[i] + b.cords[i];
    }
    return temp;
}

Point Point::operator-(const Point& b) {
    Point temp = Point();
    for (int i = 0; i < dimensions; i++) {
        temp.cords[i] = cords[i] - b.cords[i];
    }
    return temp;
}

Point Point::operator*(const int k) {
    Point temp = Point();
    for (int i = 0; i < dimensions; i++) {
        temp.cords[i] = cords[i] * k;
    }
    return temp;
}

Point Point::operator/(const int k) {
    Point temp = Point();
    for (int i = 0; i < dimensions; i++) {
        temp.cords[i] = cords[i] / k;
    }
    return temp;
}

ostream& operator<<(ostream& os, const Point& p) {
    os << "(";
    for (int i = 0; i < p.dimensions - 1; i++) {
        os << p.cords[i] << ", ";
    }
    os << p.cords[p.dimensions - 1] << ")";
    return os;
}