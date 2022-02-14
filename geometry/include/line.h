#ifndef LINE_H
#define LINE_H

#include <vector>

#include "point.h"
using namespace std;

class Line {
    int count;
    vector<Point> cords;

   public:
    Line();
    void add_point(const Point& p);
    void delete_point(int num);
    Point get_point(int num);
    long double perimeter();

    Line operator+(const Line& b);
    Line operator-(const Line& b);

    void operator+=(const Line& b);
    void operator-=(const Line& b);    

    bool operator==(const Line& b);
    bool operator!=(const Line& b);

   private:
};

#endif `