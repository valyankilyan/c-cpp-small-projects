#include "../include/line.h"

#include <iostream>
#include <limits>

using namespace std;

Line::Line() {}

Line::Line(Line* l) {
    validate();
    cords = vector<Point>();
    for (int i = 0; i < l->size(); i++) {
        if (validate()) {
            cords.push_back(l->operator[](i));
        } else {
            cords.pop_back();
            break;
        }
    }
}

bool Line::push_back(Point p) {
    cords.push_back(p);
    if (validate()) {
        cords.pop_back();
        return 0;
    }
    return 1;
}

bool Line::pop_back() {
    if (cords.size() == 0) {
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

bool Line::add_point(size_t num, Point p) {
    if (num >= size()) {
        return 0;
    } else if (num == size()) {
        return push_back(p);
    } else {
        Point cur_point = p;
        for (size_t i = num; i < size(); i++) {
            Point save = cords[i];
            cords[i] = cur_point;
            cur_point = save;
        }
        cords.push_back(cur_point);
        if (validate()) {
            return 1;
        } else {
            return delete_point(num);
        }
    }
}

bool Line::delete_point(size_t num) {
    if (num >= size()) {
        return 0;
    } else if (num == size()) {
        return pop_back();
    } else {
        Point save = cords[num];
        for (size_t i = num; i < size() - 1; i++) {
            cords[i] = cords[i + 1];
        }
        cords.pop_back();
        if (validate()) {
            return 1;
        } else {
            return add_point(num, save);
        }
    }
}

Point& Line::get_point(size_t num) {
    return cords[num];
}

Point& Line::operator[](size_t num) {
    return Line::get_point(num);
}

int Line::size() const {
    return cords.size();
}

long double Line::perimeter() const {
    long double ans = 0;
    for (size_t i = 0; i < size() - 1; i++) {
        ans += cords[i].vector_lenght(cords[i + 1]);
    }
    return ans + cords[0].vector_lenght(cords[size() - 1]);
}

Line Line::operator+(const Line& l) {
    Line temp = *this;
    for (auto p : l.cords) {
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
    for (auto& p : l.cords) {
        push_back(p);
    }
}

void Line::operator+=(const Point& p) {
    push_back(p);
}

bool Line::operator==(const Line& line) {
    bool ans = this->cords.size() == line.cords.size();
    auto it1 = this->cords.begin();
    auto it2 = line.cords.begin();
    for (int i = 0; i < this->size() && ans; i++) {
        ans = ans && (cords[i] == line.cords[i]);
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


bool Line::find_coefficients(long double* k, long double* b, Point* f, Point* s) {
    if (*f == *s) {
        return 0;
    }
    *k = ((*f)[0] - (*s)[0]) / ((*f)[1] - (*s)[1]);
    *b = (*f)[0] - *k * (*f)[1];
    return 1;
}

bool Line::same_straight_check(Point* a, Point* b, Point* c) {
    long double K, B;
    if (!find_coefficients(&K, &B, a, b)) {
        return 1;
    }
    return abs((*c)[0]*K + B - (*c)[1]) < eps;
}

bool Line::is_between(const Point* a, const Point* b, const Point* c) {
    return (*c)[0] > min((*a)[0], (*b)[0]) &&
           (*c)[0] < max((*a)[0], (*b)[0]);
}

bool Line::is_done() {
    return size() > 1;
}

bool Line::validate() {
    cout << "Line validation" << endl;
    if (size() < 3) {
        return true;
    }

    bool ans = 0;
    for (size_t i = 0; i < size() - 2; i++) {
        ans = ans && !same_straight_check(&cords[i], &cords[i+1], &cords[i+2]);
    }
    if (ans) {
        ans = ans && !same_straight_check(&cords[size()-2], &cords[size() - 1], &cords[0]);
        ans = ans && !same_straight_check(&cords[0], &cords[size() - 1], &cords[1]);
    }

    if (!ans) validation_error("line");
    return ans;
}

void Line::validation_error(string location) {
    cerr << " {Validation error in " << location << "} ";
}
