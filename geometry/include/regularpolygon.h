#ifndef REGULAR_POLYGON_H
#define REGULAR_POLYGON_H

#include "polygon.h"
#include "segment.h"

class RegularPolygon : public Polygon {
   public:
    RegularPolygon();

    RegularPolygon(Point o, long double R, int n, long double phi);

    void from_circle(Point o, long double R, int n, long double phi);

   protected:

    virtual bool validate() override;
};

#endif