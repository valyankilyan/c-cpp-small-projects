#ifndef POINT_H
#define POINT_H

#include <ostream>
#include <utility>
using namespace std;

class Point {
    int dimensions;
    long double* cords;

   public:
    /**
     * @brief Construct a new Point object
     *
     */
    Point();

    /**
     * @brief Construct a new Point object
     *
     * @param x first cord
     * @param y second cord
     */
    Point(long double x, long double y);

    /**
     * @brief Construct a new Point object from Point
     *
     * @param point
     */
    Point(const Point& point);

    /**
     * @brief Destroy the Point object
     *
     */
    ~Point();

    /**
     * @brief Edits Point coordinates
     *
     * @param x
     * @param y
     */
    void set(long double x, long double y);

    /**
     * @brief Returns pair of Point coordinates
     *
     * @return pair<long double, long double> coordinates
     */
    pair<long double, long double> get();

    /**
     * @brief Get the dimensions conunt
     *
     * @return int
     */
    int get_dimensions();

    /**
     * @brief Returns vector lenght from this to point
     *
     * @param point end of the vector
     * @return long double vector length
     */
    long double vector_lenght(const Point& point);

    /**
     * @brief Adds each coordinate
     *
     * @param point
     * @return Point
     */
    Point operator+(const Point& point);

    /**
     * @brief Substracts each coordinate
     *
     * @param point
     * @return Point
     */
    Point operator-(const Point& point);

    /**
     * @brief Multiplies each coordinate by coefficient
     *
     * @param k
     * @return Point
     */
    Point operator*(const long double k);

    /**
     * @brief Divides each coordinate by coefficient
     *
     * @param k
     * @return Point
     */
    Point operator/(const long double k);

    /**
     * @brief Adds each coordinate
     *
     * @param point
     */
    void operator+=(const Point& point);

    /**
     * @brief Subtracts each coordinate
     *
     * @param point
     */
    void operator-=(const Point& point);

    /**
     * @brief Multiplies each coordinate by coefficient
     *
     * @param k
     */
    void operator*=(const long double k);

    /**
     * @brief Divides each coordinate by coefficient
     *
     * @param k
     */
    void operator/=(const long double k);

    /**
     * @brief
     *
     * @param point
     * @return true all coordinate are equal
     * @return false another condition
     */
    bool operator==(const Point& point);

    /**
     * @brief
     *
     * @param point
     * @return true another condition
     * @return false all coordinate are equal
     */
    bool operator!=(const Point& point);

    /**
     * @brief Copying one point to this point
     *
     * @param point
     */
    void operator=(const Point& point);

    /**
     * @brief Returns a read/write reference to the num_th coordinate
     *
     * @param num
     * @return long double
     */
    long double& operator[](int num);

    /**
     * @brief Operator for out stream
     * 
     * @param os stream
     * @param point
     * @return ostream& 
     */
    friend ostream& operator<<(ostream& os, const Point& point);

    /**
     * @brief Operator for cin stream
     * 
     * @param is 
     * @param point
     * @return istream& 
     */
    friend istream& operator>>(istream& is, Point& point);
};

#endif