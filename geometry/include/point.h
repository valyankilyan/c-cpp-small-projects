#ifndef POINT_H
#define POINT_H

#include <utility>
using namespace std;

class Point {
   private:
    int dimensions = 2;
    int* cords;

   public:
    Point(int x, int y);
    void set(int x, int y);
    pair<int, int> get();
    void print();
    ~Point();
};

#endif