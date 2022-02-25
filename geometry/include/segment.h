#ifndef SEGMENT_H
#define SEGMENT_H

#include "line.h"
#include "point.h"

class Segment : public Line {
   public:
    /**
     * @brief Construct a new Segment object
     *
     */
    Segment();

    /**
     * @brief Construct a new Segment object from two first points of line
     *
     * @param line
     */
    Segment(Line* line);

    /**
     * @brief Construct a new Segment object from 2 points
     *
     * @param a
     * @param b
     */
    Segment(Point a, Point b);

   protected:
    /**
     * @brief checks whether Segment is done
     *
     * @return true
     * @return false
     */
    virtual bool is_done() override;

    /**
     * @brief validate segment
     *
     * @return true
     * @return false
     */
    virtual bool validate() override;
};

#endif