#include "../include/line.h"

#include <iostream>
#include <limits>

using namespace std;

Line::Line() {}

Line::Line(const Line* l) {
    cout << "first const\n"
         << endl;
    for (auto& p : l->cords) {
        cords.push_back(p);
    }
}

// Line Line::operator=(const Line* l) {
//     cout << "second const\n" << endl;
//     for (auto &p: l->cords) {
//         cords.push_back(p);
//     }
//     return *this;
// }

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
    if (this->cords.size() == 0) {
        return 0;
    }
    Point save = this->front();
    cords.pop_front();
    if (!this->validate()) {
        cords.push_front(save);
        return 0;
    }
    return 1;
}

bool Line::pop_back() {
    if (this->cords.size() == 0) {
        return 0;
    }
    Point save = cords.back();
    cords.pop_back();
    if (!this->validate()) {
        cords.push_back(save);
        return 0;
    }
    return 1;
}

Point& Line::front() {
    return cords.front();
}

Point& Line::back() {
    return cords.back();
}

bool Line::add_point(size_t num, Point p) {
    auto it = this->find_iter(num);
    if (it == cords.end()) {
        return 0;
    }
    cords.emplace(it, p);
    return 1;
}

bool Line::delete_point(size_t num) {
    auto it = this->find_iter(num);
    if (it == cords.end()) {
        return 0;
    }
    cords.erase(it);
    return 1;
}

Point& Line::get_point(size_t num) {
    if (num >= cords.size()) {
        return *cords.rbegin();
    }
    auto it = Line::find_iter(num);
    return *it;
}

Point& Line::operator[](size_t num) {
    return Line::get_point(num);
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

bool Line::operator==(const Line& line) {
    bool ans = this->cords.size() == line.cords.size();
    auto it1 = this->cords.begin();
    auto it2 = line.cords.begin();
    for (int i = 0; ans && it1 != this->cords.end(); i++) {
        ans = ans && (*it1 == *it2);
        it1++;
        it2++;
    }
    return ans;
}

bool Line::operator!=(const Line& line) {
    return !(Line::operator==(line));
}

ostream& operator<<(ostream& os, const Line& l) {
    int d = l.cords.size();
    os << "[";
    for (auto p : l.cords) {
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
    os << "]";
    return os;
}

// long double ClosedLine::perimeter() {
//     long double ans = Line::perimeter();
//     return ans + this->front().vector_lenght(this->back());
// }

_List_iterator<Point> Line::find_iter(size_t num) {
    if (num >= cords.size()) {
        return cords.end();
    }
    auto it = cords.begin();
    while (num--) {
        it++;
    }
    return it;
}

bool Line::one_straight_check(_List_iterator<Point> a[]) {
    long double k, b;
    k = ((*(a[0]))[0] - (*(a[1]))[0]) / ((*(a[0]))[1] - (*(a[1]))[1]);
    b = (*(a[0]))[0] - k * (*(a[0]))[1];
    return (*(a[2]))[0] == (k * (*(a[2]))[1] + b);
}

bool Line::validate() {
    if (size() < 3) {
        return true;
    }
    _List_iterator<Point> a[3];
    for (int i = 0; i < 3; i++) {
        a[i] = find_iter(i);
    }

    bool ans = 1;
    while (ans && a[2] != cords.end()) {
        ans = ans && !one_straight_check(a);
        for (int i = 0; i < 3; i++) {
            a[i]++;
        }
    }
    if (ans) {
        a[2] = cords.begin();
        ans = ans && !one_straight_check(a);
    }
    return ans;
}

