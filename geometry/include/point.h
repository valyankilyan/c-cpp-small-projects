#ifndef POINT_H
#define POINT_H

#include <ostream>
#include <utility>
using namespace std;

class Point {
   private:
    int dimensions;
    long double* cords;

   public:
    Point(long double x, long double y);
    Point();
    void set(long double x, long double y);
    pair<long double, long double> get();    
    ~Point();

    Point operator+ (const Point &b);
    Point operator- (const Point &b);
    Point operator* (const int k);
    Point operator/ (const int k);

    friend ostream& operator<<(ostream& os, const Point& p);
};

#endif