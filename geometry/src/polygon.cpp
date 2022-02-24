#include "../include/polygon.h"

#include <iostream>

Polygon::Polygon() {}

Polygon::Polygon(Line* l) {
    cords = vector<Point>();
    for (size_t i = 0; i < l->size(); i++) {
        push_back(l->operator[](i));
    }
}

long double Polygon::area() {
    long double a = 0, b = 0;
    for (size_t i = 0; i < size() - 1; i++) {
        cerr << i << endl;
        a += cords[i][0] * cords[i + 1][1];
        b += cords[i][1] * cords[i + 1][0];
    }
    a += cords[size() - 1][0] * cords[0][1];
    b += cords[size() - 1][1] * cords[0][0];

    return (a - b) / 2;
}

bool Polygon::find_intersection(Point* a1, Point* a2, Point* b1, Point* b2) {
    long double K1, K2, B1, B2;
    find_coefficients(&K1, &B1, a1, a2);
    find_coefficients(&K2, &B2, b1, b2);

    if (K1 == K2) {
        if (B1 == B2) {
            return 1;
        } else {
            return 0;
        }
    } else {
        bool out = 1;
        out = out && is_between(a1, a2, b1);
        out = out && is_between(a1, a2, b2);
        return out;
    }

    return 0;
}

bool Polygon::validate() {
    cout << "Polygon validation\n";
    if (!ClosedLine::validate()) {
        return 0;
    } else if (size() < 3) {
        return 1;
    }

    bool ans = 1;
    for (size_t i = 0; i < size() - 3 && ans; i++) {
        for (size_t j = i + 2; j < size() - 1 && ans; j++) {
            ans = ans && !find_intersection(&cords[i], &cords[i+1], &cords[j], &cords[j+1]);
        }        
    }
    if (!ans) validation_error("polygon");
    return ans;
}