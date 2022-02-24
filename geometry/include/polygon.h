#ifndef POLYGON_H
#define POLYGON_H

#include "closedline.h"

class Polygon : public ClosedLine {
   public:
    using ClosedLine::ClosedLine;

    /**
     * @brief Returns area of the figure
     * 
     * @return long double 
     */
    long double area();

   protected:
    /**
     * @brief Returns true if segments intersects
     * and puts Point of intersection into ans
     *
     * @param a first line segment
     * @param b second line segments
     * @param ans Point answer
     * @return true
     * @return false
     */
    bool find_intersection(const Point* a1, const Point* a2, const Point* b1, const Point* b2, const Point* ans);

    /**
     * @brief Returns true if validation passed
     *
     * @return true
     * @return false
     */
    virtual bool validate() override;
};

#endif