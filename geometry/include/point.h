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
    Point();
    Point(long double x, long double y);
    Point(const Point& p);
    void set(long double x, long double y);
    pair<long double, long double> get();
    ~Point();

    Point operator+(const Point& b);
    Point operator-(const Point& b);
    Point operator*(const int k);
    Point operator/(const int k);
    
    void operator+=(const Point& b);
    void operator-=(const Point& b);
    void operator*=(const int k);
    void operator/=(const int k);

    bool operator==(const Point& b);
    bool operator!=(const Point& b);

    friend ostream& operator<<(ostream& os, const Point& p);
};

#endif