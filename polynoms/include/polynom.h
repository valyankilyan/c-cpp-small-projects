#ifndef POLYNOM_H
#define POLYNOM_H

#include <vector>
#include <iostream>
#include <cmath>

#define MAX 1000006

using namespace std;

class Polynom {
    public:
    Polynom();
    Polynom(Polynom &p);
    Polynom operator=(Polynom &p);
    bool operator==(Polynom &p);
    bool operator!=(Polynom &p);
    Polynom operator+(Polynom &p);
    Polynom operator-(Polynom &p);
    void operator+=(Polynom &p);
    void operator-=(Polynom &p);
    Polynom operator*(long double k);
    Polynom operator/(long double k);
    void operator*=(long double k);
    void operator/=(long double k);

    friend ostream& operator<<(ostream& os, Polynom &p);
    friend istream& operator>>(istream& is, Polynom &p);

    long double& operator[](size_t num);

    size_t size();

    private:
    vector <long double> coef;
};

ostream& operator<<(ostream& os, Polynom &p);
istream& operator>>(istream& is, Polynom &p);

#endif