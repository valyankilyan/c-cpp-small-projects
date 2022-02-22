#include "../include/closedline.h"

long double ClosedLine::perimeter() {
    long double ans = Line::perimeter();
    return ans + this->front().vector_lenght(this->back());
}

bool ClosedLine::is_done() {
    return size() > 2;
}