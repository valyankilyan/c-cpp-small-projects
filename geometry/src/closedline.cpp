#include "../include/closedline.h"

#include <iostream>

long double ClosedLine::perimeter() {
    long double ans = Line::perimeter();
    return ans + cords[0].vector_lenght(cords[size() - 1]);
}

bool ClosedLine::is_done() {
    return size() > 2;
}

bool ClosedLine::validate() {
    cout << "ClosedLine validation\n";
    return Line::validate();
}