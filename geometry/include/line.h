#ifndef LINE_H
#define LINE_H

#include <vector>

#include "point.h"

using namespace std;

#define eps 0.00001

class Line {
   public:
    /**
     * @brief Construct an empty object
     */
    Line();
    /**
     * @brief Copying construct
     *
     * @param line src
     */
    Line(Line* line);
    // Line operator=(const Line* l);

    /**
     * @brief add Point to the end of the line
     *
     * @param point
     * @return true if successed
     * @return false if validation failed
     */
    bool push_back(Point point);

    /**
     * @brief Removes last Point of the line
     *
     * @return true if successed
     * @return false if validation failed
     */
    bool pop_back();

    /**
     * @brief returns the last element of the line
     *
     * @return Point&
     */
    Point& back();

    /**
     * @brief Adds point on num_th place
     * 
     * @param num number of the Point
     * @param point src
     * @return true if successed
     * @return false if not validated
     */
    bool add_point(size_t num, Point point);

    /**
     * @brief Deletes num_th Point of the Line
     *
     * @param num - number of the point
     * @return true if successed
     * @return false if not validated
     */
    bool delete_point(size_t num);

    /**
     * @brief clears the Line
     * 
     */
    void clear();

    /**
     * @brief Get the point object
     *
     * @param num
     * @return Point&
     */
    Point& get_point(size_t num);

    /**
     * @brief Return a read/write reference to the num_th Point
     *
     * @param num
     * @return Point&
     */
    Point& operator[](size_t num);

    /**
     * @brief Returns count of the Points in line
     *
     * @return int size
     */
    size_t size() const;

    /**
     * @brief Calculates the length of the figure
     *
     * @return long double length
     */
    long double perimeter() const;

    /**
     * @brief Returns true if Figure is done
     *
     * @return true
     * @return false
     */
    virtual bool is_done();

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

    /**
     * @brief Returns the representation in out ostream
     *
     * @param os
     * @param p
     * @return ostream&
     */
    friend ostream& operator<<(ostream& os, const Line& p);

   protected:
    /**
     * @brief Returns coefficients of the line equation for vector
     *
     * @param k first coefficient
     * @param b second coefficient
     * @param a const first Point
     * @param b const second Point
     */
    bool find_coefficients(long double* k, long double* b, Point* f, Point* s);

    /**
     * @brief Returns true if a[0], a[1] and a[2] in the same straight line
     *
     * @param a array of Points with a size of 3
     * @return true
     * @return false
     */
    bool same_straight_check(Point* a, Point* b, Point* c);

    /**
     * @brief Returns true if b is between a1 and a2
     *
     * @param a1
     * @param a2
     * @param b
     * @return true
     * @return false
     */
    bool is_between(const Point* a1, const Point* a2, const Point* b);

    /**
     * @brief Returns true if validation passed
     *
     * @return true
     * @return false
     */
    virtual bool validate();

    /**
     * @brief printing validation error in stderr
     *
     * @param location validation class in wich error was found
     */
    void validation_error(string location);

    /**
     * @brief Points of line
     *
     */
    vector<Point> cords;
};

#endif