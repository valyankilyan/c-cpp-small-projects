#include "../include/line.h"

using namespace std;

Line::Line() {}

Line::Line(const Line& l) : cords(this->cords = l.cords){}

Line Line::operator=(const Line& l) {
    cords = l.cords;
    return *this;
}

bool Line::push_front(Point p) {
    cords.push_front(p);
    if (!this->validate()) {
        cords.pop_front();
        return 0;
    }
    return 1;
}

bool Line::push_back(Point p) {
    cords.push_back(p);
    if (!this->validate()) {
        cords.pop_back();
        return 0;
    }
    return 1;
}

bool Line::pop_front() {
    Point save = this->front();
    cords.pop_front();
    if (!this->validate()) {
        cords.push_front(save);
        return 0;
    }
    return 1;
}

bool Line::pop_back() {
    Point save = cords.back();
    cords.pop_back();
    if (!this->validate()) {
        cords.push_back(save);
        return 0;
    }
    return 1;
}

bool Line::delete_point(long unsigned int num) {
    if (num >= cords.size()) {
        return 0;
    }
    auto it = cords.begin();
    while (num--) {
        it++;
    }
    Point save = Point(*it);
    it = cords.erase(it);
    if (!this->validate()) {        
        cords.emplace(it, save);
    }
    return 1;
}

Point Line::front() {
    if (cords.empty()) {
        return Point(0, 0);
    }
    return cords.front();
}

Point Line::back() {
    if (cords.empty()) {
        return Point(0, 0);
    }
    return cords.back();
}

bool Line::set_point(long unsigned int num, Point p) {
    if (num >= cords.size()) {
        return 0;
    }
    auto it = cords.begin();
    while (num--) {
        it++;
    }
    cords.emplace(it, p);
    return 1;
}

Point Line::get_point(long unsigned int num) {
    if (num >= cords.size()) {
        return Point();
    }
    auto it = cords.begin();
    while (num--) {
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
        ans += (*it).vector_lenght(last);
        last = *it;
    }
    return ans;
}

Line Line::operator+(const Line& l) {
    Line temp = *this;
    for (auto p: l.cords) {
        temp.push_back(p);
    }
    return temp;
}

Line Line::operator+(const Point& p) {
    Line temp = *this;
    temp.push_back(p);
    return temp;
}

void Line::operator+=(const Line& l) {
    for (auto p: l.cords) {
        this->push_back(p);
    }
}

void Line::operator+=(const Point& p) {
    this->push_back(p);
}

ostream& operator<<(ostream& os, const Line& l) {
    int d = l.cords.size();
    for (auto p: l.cords) {
        d--;
        os << "(";
        int i = 0;
        for (i = 0; i < p.get_dimensions() - 1; i++) {
            os << p[i] << ", ";
        }
        os << p[i] << ")";
        if (d) {
            os << " -> ";
        }
    }
    return os;
}

long double ClosedLine::perimeter() {
    long double ans = Line::perimeter();    
    return ans + this->front().vector_lenght(this->back());
}

bool Line::validate() {
    return 1;
}

bool ClosedLine::validate() {
    return 1;
}