#include "../include/polynom.h"

Polynom::Polynom() {}

Polynom::Polynom(Polynom &p) {
    for (size_t i = 0; i < p.coef.size(); i++) {
        this->coef.push_back(p[i]);
    }
}
Polynom Polynom::operator=(Polynom &p) {
    for (size_t i = 0; i < p.coef.size(); i++) {
        this->coef.push_back(p[i]);
    }
    return (*this);
}
bool Polynom::operator==(Polynom &p) {
    if (size() != size()) {
        return 0;
    }
    bool ans = 1;
    for (size_t i = 0; i < size() && ans; i++) {
        ans = ans && coef[i] == p.coef[i];
    }
    return ans;
}
bool Polynom::operator!=(Polynom &p) {
    return !operator==(p);
}
Polynom Polynom::operator+(Polynom &p) {
    Polynom out;
    out += *this;
    out += p;
    return out;
}
Polynom Polynom::operator-(Polynom &p) {
    Polynom out;
    out += *this;
    out -= p;
    return out;
}
void Polynom::operator+=(Polynom &p) {
    for (size_t i = 0; i < p.size(); i++) {
        (*this)[i] += p[i];
    }
}
void Polynom::operator-=(Polynom &p) {
    for (size_t i = 0; i < p.size(); i++) {
        (*this)[i] -= p[i];
    }
}

Polynom Polynom::operator*(long double k) {
    Polynom out = *this;
    for (size_t i = 0; i < size(); i++) {
        (*this)[i] *= k;
    }
    return out;
}
Polynom Polynom::operator/(long double k) {
    Polynom out = *this;
    for (size_t i = 0; i < size(); i++) {
        (*this)[i] /= k;
    }
    return out;
}
void Polynom::operator*=(long double k) {
    for (size_t i = 0; i < size(); i++) {
        (*this)[i] *= k;
    }
}
void Polynom::operator/=(long double k) {
    for (size_t i = 0; i < size(); i++) {
        (*this)[i] /= k;
    }
}

ostream &operator<<(ostream &os, Polynom &p) {
    for (size_t i = p.size() - 1; i > 0; i--) {
        if (p[i] != 0) {
            os << p[i] << "x^" << i << " + ";
        }
    }
    if (p[0] != 0) {
        os << p[0];
    }
    return os;
}
istream &operator>>(istream &is, Polynom &p) {
    int n;
    is >> n;
    for (int i = 0; i < n; i++) {
        long double c;
        is >> c;
        p.coef.push_back(c);
    }
    return is;
}

long double &Polynom::operator[](size_t num) {
    if (num >= MAX) {
        cout << "too large power..\n";
        return coef[0];
    }
    if (num > size()) {
        coef.resize(num + 1);
    }
    return coef[num];
}

size_t Polynom::size() {
    return coef.size();
}