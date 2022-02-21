#ifndef POLYGON_H
#define POLYGON_H

#include "line.h"

class Polygon : public ClosedLine {
   private:
    bool validate();
};

#endif