#include <iostream>

#include "../include/point.h"
#include "../include/line.h"
using namespace std;

int main() {
    Point p1 = Point(1, 2);
    Point p2 = Point();
    cin >> p2;

    cout << endl;
    cout << p1 << " + " << p2 << " = " << p1 + p2 << endl;
    cout << p1 << " - " << p2 << " = " << p1 - p2 << endl;
    cout << p1 << " * " << 10 << " = " << p1 * 10 << endl;
    cout << p1 << " / " << 10 << " = " << p1 / 10 << endl;

    Point p3 = p1;
    cout << "p3 = " << p3 << endl;
    p3+= p1;
    cout << "p3+= p1 = " << p3 << endl;
    p3-= p1;
    cout << "p3-= p1 = " << p3 << endl;
    p3/= 2;
    cout << "p3/= 2 = " << p3 << endl;
    p3*= 2;
    cout << "p3*=2 = " << p3 << endl;

    cout << "p1 == p3 = " << (p1 == p3) << endl;
    cout << "p1 != p2 = " << (p1 != p2) << endl;
    

    // delete p1;
    // delete p2;
}