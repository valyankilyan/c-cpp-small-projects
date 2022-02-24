#include "../include/polygon.h"
#include <iostream>

long double Polygon::area() {
    long double a = 0, b = 0;
    for (int i = 0; i < size(); i++) {
        a+= cords[i][0] * cords[i + 1][1];
        b+= cords[i][1] * cords[i + 1][0];        
    }
    a+= cords[size() - 1][0] * cords[0][1];
    b+= cords[size() - 1][1] * cords[0][0];        
    
    return (a - b) / 2;
}

bool find_intersection(const Point* a1, const Point* a2, const Point* b1, const Point* b2, Point* ans=NULL) {
    long double k1, k2, b1, b2;
    
    
    // find_coefficients(&k1, &b1, &(*(a[0])), &(*(a[1])));
    // find_coefficients(&k2, &b2, &(*(b[0])), &(*(b[1])));
    // if (k1 == k2) {
    //     if (b1 == b2) {
    //         bool out = 1;
    //         out = out && is_between(&(*a[0]), &(*a[1]), &(*b[0]));
    //         out = out && is_between(&(*a[0]), &(*a[1]), &(*b[1]));
    //         return out;
    //     }
    //     return 0;
    // }
    // long double x = (b2 - b1) / (k1 - k2);
    // long double y = k1 * x + b1;
    // Point intersection(x, y);
    // bool out = 1;
    // out = out && is_between(&(*a[0]), &(*a[1]), &intersection);
    // out = out && is_between(&(*a[0]), &(*a[1]), &intersection);
    // if (ans && out) {
    //     ans->set(x, y);
    // }

    // return out;
}

bool Polygon::validate() {    
    cout << "Polygon validation\n";
    if (!ClosedLine::validate()) {
        return 0;
    }

    lit a[2], b[2];
    a[0] = find_iter(0);
    a[1] = a[0];
    a[1]++;
    bool ans = 1;
    for (int i = 0; i < size() - 3 && ans; i++) {
        b[0] = a[1];
        b[0]++;
        b[1] = b[0];
        b[1]++;
        for (int j = i + 2; j < size() - 1 && ans; i++) {
            ans = ans && !find_intersection(a, b);
            b[0]++;
            b[1]++;
        }
        a[0]++;
        a[1]++;
    }
    if (!ans) validation_error("polygon");
    return ans;
}