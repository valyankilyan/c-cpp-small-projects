#include "../include/polynom.h"
#include <iostream>

using namespace std;

int main() {
    Polynom p;
    cin >> p;
    cout << p << endl;
    p[10] = 2;
    cout << p << endl;

}