#ifndef CLOSEDLINE_H
#define CLOSEDLINE_H

#include "line.h"

class ClosedLine : public Line {
   public:
    using Line::Line;
    /**
     * @brief Returns perimeter of the closed line
     *
     * @return long double
     */

    long double perimeter();

    bool is_done();
};

#endif