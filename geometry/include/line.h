#ifndef LINE_H
#define LINE_H

#include <list>

#include "point.h"
using namespace std;

class Line {    
    list<Point> cords;

   public:
    Line();    
    void push_front(Point p);
    void push_back(Point p);
    void pop_back();
    void pop_front();

    void set_point(long unsigned int num, Point p);
    void delete_point(long unsigned int num);
    
    Point get_point(long unsigned int num);
    int size();
    long double perimeter();

    Line operator+(const Line& b);
    Line operator-(const Line& b);

    void operator+=(const Line& b);
    void operator-=(const Line& b);    

    bool operator==(const Line& b);
    bool operator!=(const Line& b);

    friend ostream& operator<<(ostream& os, const Point& p);

   private:
};

#endif