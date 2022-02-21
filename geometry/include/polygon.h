#ifndef POLYGON_H
#define POLYGON_H

#include "line.h"

class Polygon : public ClosedLine {
   protected:
    bool validate();
};

#endif