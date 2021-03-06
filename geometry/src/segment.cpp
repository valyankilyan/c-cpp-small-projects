#include "../include/segment.h"

Segment::Segment() {}

Segment::Segment(Line *l) {
    cords = vector<Point>();
    for (size_t i = 0; i < min(l->size(), (size_t)3); i++) {
        push_back(l->operator[](i));
    }
}

Segment::Segment(Point a, Point b) {
    cords.push_back(a);
    cords.push_back(b);
}

bool Segment::is_done() {
    return size() == 2;
}

bool Segment::validate() {
    return size() == 2 && cords[0] != cords[1];
}