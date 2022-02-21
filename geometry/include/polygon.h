#ifndef POLYGON_H
#define POLYGON_H

#include "line.h"

class Polygon : public ClosedLine {
   protected:
   /**
    * @brief Finds intersection coordinates
    * 
    * @param a first line segment
    * @param b second line segments
    * @param ans Point answer
    * @return true 
    * @return false 
    */
    bool find_intersection(lit *a, lit *b, Point* ans);

    /**
     * @brief Returns true if segments intersect
     * 
     * @param a first line segment
     * @param b second line segment
     * @return true 
     * @return false 
     */
    bool intersect(lit *a, lit *b);

    /**
     * @brief validates polygon
     *
     * @return true
     * @return false
     */
    bool validate();

};

#endif