#include "../include/point.h"
using namespace std;

int main() {
    Point *p1 = new Point(1, 2);
    Point *p2 = new Point(10, 20);
    
    p1->print();
    p2->print();
    delete p1;
    delete p2;
}