#include "../include/line.h"

using namespace std;

Line::Line() {}

void Line::push_back(Point p) {    
    cords.push_back(p);
}

void Line::push_front(Point p) {
    cords.push_front(p);
}

void Line::delete_point(long unsigned int num) {
    if (num >= cords.size()) {
        return;
    }
    auto it = cords.begin();
    while(num--) {
        it++;
    }
    cords.erase(it);    
}

void Line::pop_back() {
    cords.pop_back();
}

void Line::pop_front() {
    cords.pop_front();
}

void Line::set_point(long unsigned int num, Point p) {
    if (num >= cords.size()) {
        return;
    }
    auto it = cords.begin();
    while(num--) {        
        it++;
    }
    cords.emplace(it, p);
}

Point Line::get_point(long unsigned int num) {
    if (num >= cords.size()) {
        return Point();
    }
    auto it = cords.begin();
    while(num--) {        
        it++;
    }
    return *it;
}

int Line::size() {
    return cords.size();
}

long double Line::perimeter() {
    long double ans = 0;
    auto it = cords.begin();
    Point last = *it;
    while (++it != cords.end()) {
        ans+= (*it).vector_lenght(last);
        last = *it;
    }
    return ans;
}

Line operator+(const Line& b);
Line operator-(const Line& b);

// void Point::operator+=(const Line& b);
// void Point::operator-=(const Line& b);

// bool Point::operator==(const Line& b);
// bool Point::operator!=(const Line& b);