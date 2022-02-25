#ifndef SEGMENT_H
#define SEGMENT_H

#include "line.h"
#include "point.h"

class Segment : Line {
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
    Segment(Line *line);

   private:
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