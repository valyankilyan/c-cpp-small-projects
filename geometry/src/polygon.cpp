#include "../include/polygon.h"

bool find_intersection(lit *a, lit *b, Point *ans) {

}

bool intersect(lit *a, lit *b) {

}

bool Polygon::validate() {
    if (!Line::validate()) {
        return 0;
    }

    lit a[2], b[2];
    a[0] = find_iter(0);
    a[1] = a[0];
    a[1]++;
    for (int i = 0; i < size() - 3; i++) {
        b[0] = a[1];
        b[0]++;
        b[1] = b[0];
        b[1]++;
        for (int j = i + 2; j < size() - 1; i++) {

        }
        a[0]++;
        a[1]++;
    }

}