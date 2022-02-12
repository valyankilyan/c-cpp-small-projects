#include <iostream>

#include "../include/point.h"
using namespace std;

int main() {
    Point p1 = Point(1, 2);
    Point p2 = Point(10, 20);    

    cout << endl;
    cout << p1 << " + " << p2 << " = " << p1 + p2 << endl;
    cout << p1 << " - " << p2 << " = " << p1 - p2 << endl;
    cout << p1 << " * " << 10 << " = " << p1 * 10 << endl;
    cout << p1 << " / " << 10 << " = " << p1 / 10 << endl;

    // delete p1;
    // delete p2;
}