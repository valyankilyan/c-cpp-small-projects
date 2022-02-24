#include "../include/point.h"

#include <iostream>
#include <utility>
#include <math.h>
using namespace std;

Point::Point()
    : dimensions(2), cords(new long double[this->dimensions]) {}

Point::Point(long double x, long double y) : dimensions(2) {
    this->cords = new long double[dimensions];
    this->cords[0] = x;
    this->cords[1] = y;
}

Point::Point(const Point& p)
    : dimensions(p.dimensions), cords(new long double[this->dimensions]) {
    for (int i = 0; i < p.dimensions; i++) {
        this->cords[i] = p.cords[i];
    }
}

Point::~Point() {
    delete[] cords;
}

void Point::set(long double x, long double y) {
    this->cords[0] = x;
    this->cords[1] = y;
}

void Point::operator=(const Point& b) {
    delete[] this->cords;
    this->dimensions = b.dimensions;
    this->cords = new long double[dimensions];
    for (int i = 0; i < dimensions; i++) {
        this->cords[i] = b.cords[i];
    }
}

pair<long double, long double> Point::get() {
    return make_pair(this->cords[0], this->cords[1]);
}

int Point::get_dimensions() {
    return this->dimensions;
}

long double Point::vector_lenght(const Point& b) const {
    long double sum = 0;
    for (int i = 0; i < this->dimensions; i++) {
        sum += (b.cords[i] - this->cords[i])*(b.cords[i] - this->cords[i]);
    }
    return sqrtf64x(sum);
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

Point Point::operator*(const long double k) {
    Point temp = Point();
    for (int i = 0; i < dimensions; i++) {
        temp.cords[i] = cords[i] * k;
    }
    return temp;
}

Point Point::operator/(const long double k) {
    Point temp = Point();
    for (int i = 0; i < dimensions; i++) {
        temp.cords[i] = cords[i] / k;
    }
    return temp;
}

void Point::operator+=(const Point& b) {
    for (int i = 0; i < dimensions; i++) {
        cords[i] += b.cords[i];
    }
}

void Point::operator-=(const Point& b) {
    for (int i = 0; i < dimensions; i++) {
        cords[i] -= b.cords[i];
    }
}
void Point::operator*=(const long double k) {
    for (int i = 0; i < dimensions; i++) {
        cords[i] *= k;
    }
}

void Point::operator/=(const long double k) {
    for (int i = 0; i < dimensions; i++) {
        cords[i] /= k;
    }
}

bool Point::operator==(const Point& b) {
    bool ans = 1;
    for (int i = 0; i < dimensions; i++) {
        ans = ans && (cords[i] == b.cords[i]);
    }
    return ans;
}

bool Point::operator!=(const Point& b) {
    return !(operator==(b));
}

long double& Point::operator[](int num) const {
    return cords[num];
}

ostream& operator<<(ostream& os, const Point& p) {
    os << "(";
    for (int i = 0; i < p.dimensions - 1; i++) {
        os << p.cords[i] << ", ";
    }
    os << p.cords[p.dimensions - 1] << ")";
    return os;
}

istream& operator>>(istream& is, Point& p) {
    p.dimensions = 2;
    is >> p.cords[0] >> p.cords[1];
    return is;
}