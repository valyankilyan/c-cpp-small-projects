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
     * @brief Adds Point to the front of the line
     *
     * @param point
     * @return true if successed
     * @return false if validation failed
     */
    bool push_front(Point point);

    /**
     * @brief add Point to the end of the line
     *
     * @param point
     * @return true if successed
     * @return false if validation failed
     */
    bool push_back(Point point);

    /**
     * @brief Removes front Point of the line
     * 
     * @return true if successed
     * @return false if validation failed
     */
    bool pop_front();

    /**
     * @brief Removes last Point of the line
     * 
     * @return true if successed
     * @return false if validation failed
     */
    bool pop_back();

    /**
     * @brief  Returns a read/write reference to the first Point
     * of the Line.
     * 
     * @return Point& 
     */
    Point& front();

    /**
     * @brief  Returns a read/write reference to the last Point
     * of the Line.
     * 
     * @return Point& 
     */
    Point& back();


    /**
     * @brief Constructs Point before the num_th iterator
     * 
     * @param num number of the Point
     * @param point src
     * @return true if successed
     * @return false if not validated
     */
    bool add_point(long unsigned int num, Point point);    

    /**
     * @brief Deletes num_th Point of the Line
     * 
     * @param num - number of the point
     * @return true if successed
     * @return false if not validated
     */
    bool delete_point(long unsigned int num);


    /**
     * @brief Returns a read/write reference to the num_th Point
     * 
     * @param num - number of the point
     * @return Point 
     */
    Point& get_point(long unsigned int num);

    /**
     * @brief Return a read/write reference to the num_th Point
     * 
     * @param num 
     * @return Point& 
     */
    Point& operator[](long unsigned int num);


    /**
     * @brief Returns count of the Points in line
     * 
     * @return int size
     */
    int size();

    /**
     * @brief Calculates the length of the figure
     * 
     * @return long double length
     */
    long double perimeter();

    /**
     * @brief Concatinates two lines
     * 
     * @param line 
     * @return Line result
     */
    Line operator+(const Line& line);

    /**
     * @brief Adds point at the end of the line
     * 
     * @param point 
     * @return Line result
     */
    Line operator+(const Point& point);


    /**
     * @brief Concatinates two lines
     * 
     * @param line 
     */
    void operator+=(const Line& line);

    /**
     * @brief Adds point at the end of the line
     * 
     * @param point 
     */
    void operator+=(const Point& point);

    /**
     * @brief Checks whether all points are equal
     * 
     * @param line 
     * @return true 
     * @return false 
     */
    bool operator==(const Line& line);

    /**
     * @brief Checks whether all points aren't equal
     * 
     * @param line 
     * @return true 
     * @return false 
     */
    bool operator!=(const Line& line);    

    friend ostream& operator<<(ostream& os, const Line& p);
    friend class ClosedLine;

    Point test();

   private:
    _List_iterator<Point> find_iter(long unsigned int num);
    bool validate();
};

class ClosedLine : public Line {
   public:
    bool operator+=(const Line& line);
    bool operator+=(const Point& point);

    long double perimeter();

   private:
    bool validate();
};

#endif