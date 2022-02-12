#ifndef POINT_H
#define POINT_H

#include <ostream>
#include <utility>
using namespace std;

class Point {
   private:
    int dimensions;
    int* cords;

   public:
    Point(int x, int y);
    Point();
    void set(int x, int y);
    pair<int, int> get();    
    ~Point();

    Point operator+ (const Point &b);
    Point operator- (const Point &b);

    friend ostream& operator<<(ostream& os, const Point& p);
};

#endif