#ifndef LINE_H
#define LINE_H

#include <list>

#include "point.h"
using namespace std;

class Line {
    list<Point> cords;

   public:
    /**
     * @brief Construct an empty Line object
     */
    Line();
    /**
     * @brief Copying construct
     *
     * @param line src
     */
    Line(const Line* line);
    // Line operator=(const Line* l);

    /**
     * @brief add Point to the front of the line
     *
     * @param point
     * @return true if validation wasn't failed
     * @return false if validation failed
     */
    bool push_front(Point point);

    /**
     * @brief add Point to the end of the line
     *
     * @param point
     * @return true if validation wasn't failed
     * @return false if validation failed
     */
    bool push_back(Point point);

    /**
     * @brief removes front Point of the line
     * 
     * @return true if validation wasn't failed
     * @return false if validation failed
     */
    bool pop_front();

    /**
     * @brief removes last Point of the line
     * 
     * @return true if validation wasn't failed
     * @return false if validation failed
     */
    bool pop_back();

    /**
     * @brief *  Returns a read/write reference to the first Point
     * of the Line.
     * 
     * @return Point& 
     */
    Point& front();

    /**
     * @brief *  Returns a read/write reference to the last Point
     * of the Line.
     * 
     * @return Point& 
     */
    Point& back();


    /**
     * @brief Constructs Point before the num_th iterator
     * 
     * @param num - number of the Point
     * @param point - src
     * @return true if validated
     * @return false if not validated
     */
    bool add_point(long unsigned int num, Point point);

    /**
     * @brief Changes num_th Point
     * 
     * @param num - number of the Point
     * @param point - src
     * @return true if validated
     * @return false if not validated
     */
    bool set_point(long unsigned int num, Point point);

    /**
     * @brief deletes num_th Point of the Line
     * 
     * @param num - number of the point
     * @return true if validated
     * @return false if not validated
     */
    bool delete_point(long unsigned int num);


    /**
     * @brief Get the num_th point object
     * 
     * @param num - number of the point
     * @return Point 
     */
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