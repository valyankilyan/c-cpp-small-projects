#include "../include/base.h"
#include "../include/derived.h"

#include <cmath>
#include <iostream>

#define PI 3.14159265
using namespace std;

int main() {
    Base base;
    Derived derived;
    base.print();
    derived.print();

    
    cout << tan(45*PI/180) << endl;
    cout << tan(0*PI/180) << endl;
    cout << tan(90*PI/180) << endl;
}