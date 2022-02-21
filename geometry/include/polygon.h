#ifndef POLYGON_H
#define POLYGON_H

#include "line.h"

class Polygon : public ClosedLine {
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
    bool find_intersection(const lit *a, const lit *b, Point* ans);

    /**
     * @brief Returns true if validation passed
     *
     * @return true
     * @return false
     */
    bool validate();

};

#endif