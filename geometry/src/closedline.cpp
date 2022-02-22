#include "../include/closedline.h"

#include <iostream>

long double ClosedLine::perimeter() {
    long double ans = Line::perimeter();
    return ans + this->front().vector_lenght(this->back());
}

bool ClosedLine::is_done() {
    return size() > 2;
}

bool ClosedLine::validate() {
    cout << "ClosedLine validation\n";
    return Line::validate();
}