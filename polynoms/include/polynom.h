#ifndef POLYNOM_H
#define POLYNOM_H

#include <vector>
#include <iostream>

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
    Polynom operator+(Member m);
    Polynom operator-(Member m);
    void operator+=(Member m);
    void operator-=(Member m);
    Polynom operator*(long double k);
    Polynom operator/(long double k);
    void operator*=(long double k);
    void operator*=(long double k);

    friend ostream& operator<<(ostream& os, Polynom &p);
    friend ostream& operator>>(ostream& os, Polynom &p);

    long double& operator[](size_t num);

    private:
    vector <long double> coef;
};

#endif