#ifndef REGULAR_POLYGON_H
#define REGULAR_POLYGON_H

#include "polygon.h"
#include "segment.h"

class RegularPolygon : public Polygon {
   public:
    /**
     * @brief Construct a new Regular Polygon object
     *
     */
    RegularPolygon();
    /**
     * @brief Construct a new Regular Polygon object from circle
     *
     * @param o centre of the circle
     * @param R radius
     * @param n count of angles
     * @param phi angle of first point from horizontal
     */
    RegularPolygon(Point o, long double R, int n, long double phi);

    /**
     * @brief Makes a new Regular Polygon object from circle
     *
     * @param o centre of the circle
     * @param R radius
     * @param n count of angles
     * @param phi angle of first point from horizontal
     */
    void from_circle(Point o, long double R, int n, long double phi);

   protected:
    /**
     * @brief validation wich is alway false
     * in case i will try to push something in here
     *
     * @return true
     * @return false
     */
    virtual bool validate() override;
};

#endif