#include "../include/regularpolygon.h"

#include <cmath>
#include <iostream>

#define PI 3.14159265

RegularPolygon::RegularPolygon() {}

RegularPolygon::RegularPolygon(Point o, long double R, int n, long double phi) {
    from_circle(o, R, n, phi);
}

void RegularPolygon::from_circle(Point o, long double R, int n, long double phi) {
    if (n < 3) {
        cout << "count of angles count could be >= 3\n"
             << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        Point cord;
        cord[0] = o[0] + R * cos(phi + 2 * PI * (long double)i / n);
        cord[1] = o[1] + R * sin(phi + 2 * PI * (long double)i / n);
        cords.push_back(cord);
    }
}

bool RegularPolygon::validate() {
    return 0;
}