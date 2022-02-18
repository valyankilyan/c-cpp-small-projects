#ifndef LINE_H
#define LINE_H

#include <list>

#include "point.h"
using namespace std;

class Line {
    list<Point> cords;

   public:
    Line();
    Line(const Line* l);
    // Line operator=(const Line* l);

    bool push_front(Point p);
    bool push_back(Point p);
    bool pop_front();
    bool pop_back();
    Point front();
    Point back();

    bool add_point(long unsigned int num, Point p);
    bool set_point(long unsigned int num, Point p);
    bool delete_point(long unsigned int num);

    Point get_point(long unsigned int num);
    int size();
    long double perimeter();

    Line operator+(const Line& b);
    Line operator+(const Point& p);

    void operator+=(const Line& b);
    void operator+=(const Point& p);

    bool operator==(const Line& b);
    bool operator!=(const Line& b);

    friend ostream& operator<<(ostream& os, const Line& p);
    friend class ClosedLine;

    Point test();

   private:
    _List_iterator<Point> find_iter(long unsigned int num);
    bool validate();
};

class ClosedLine : public Line {
   public:
    bool operator+=(const Line& b);
    bool operator+=(const Point& p);

    long double perimeter();

   private:
    bool validate();
};

#endif