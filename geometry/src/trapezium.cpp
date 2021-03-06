#include "../include/trapezium.h"

#include <iostream>

Trapezium::Trapezium() {}

Trapezium::Trapezium(Segment a, Segment b) {
    this->push_back(a[0]);
    this->push_back(a[1]);
    this->push_back(b[0]);
    this->push_back(b[1]);    
    if (!validate()) {
        this->clear();
    }
}

Trapezium::Trapezium(Line *l) {
    cords = vector<Point>();
    for (size_t i = 0; i < min(l->size(), size_t(POINT_COUNT + 1)); i++) {
        push_back(l->operator[](i));
    }
    if (is_done() && !validate()) {
        this->clear();
    }
}

bool Trapezium::is_done() {
    return size() == POINT_COUNT;
}

bool Trapezium::validate() {
    cout << "trapezium validation\n";
    if (!Polygon::validate()) {
        return 0;
    }
    if (size() > POINT_COUNT) {
        return 0;
    }
    if (!is_done()) {
        return 1;
    }
    bool ans = 0;
    long double k1, k2, b1, b2;
    size_t start = 0;
    for (start = 0; start <= 1; start++) {        
        if (!find_coefficients(&k1, &b1, &cords[start], &cords[start + 1]) ||
            !find_coefficients(&k2, &b2, &cords[start + 2], &cords[(start + 3) % POINT_COUNT])) {
            return 0;
        }
        ans = (abs(k1) == abs(k2)) && (b1 != b2);        
        if (ans) break;
    }    
    if (!ans) {
        return 0;
    }

    if (start == 1) {
        Point save;
        for (int i = POINT_COUNT; i > 0; i--) {
            save = cords[i - 1];
            cords[i - 1] = cords[i % POINT_COUNT];
        }
    }

    if (k1 == -k2) {
        auto save = cords[0];
        cords[0] = cords[1];
        cords[1] = save;
    }
    return ans;
}