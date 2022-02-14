#ifndef POINT_H
#define POINT_H

#include <ostream>
#include <utility>
using namespace std;

class Point {   
    int dimensions;
    long double* cords;

   public:
    Point();
    Point(long double x, long double y);
    Point(const Point& p);
    ~Point();
    void set(long double x, long double y);
    pair<long double, long double> get();
    long double vector_lenght(const Point& p);

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

    void operator=(const Point& b);

    long double operator[](int num);

    friend ostream& operator<<(ostream& os, const Point& p);
    friend istream& operator>>(istream& is, Point& p);
};

#endif