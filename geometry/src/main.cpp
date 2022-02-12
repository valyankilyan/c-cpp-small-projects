#include <iostream>

#include "../include/point.h"
using namespace std;

int main() {
    Point p1 = Point(1, 2);
    Point p2 = Point(10, 20);

    p1.print();
    p2.print();

    cout << endl;
    cout << p1 << " " << p2 << endl;

    // delete p1;
    // delete p2;
}